/* This includes the first function get_sockaddr which converts the Server's IP address and Port into a usable form which further creates Socket. After creating the Sockets, the next function open_connection will establish a connection to the server using sockets. */

#include "common.h"

/*
 * The function get_sockaddr converts the server's address and port into a form usable to create a socket.
*/

struct addrinfo* get_sockaddr(struct addrinfo hints, const char* hostname, const char *port){
  
  struct addrinfo* results;
  /* Use getaddrinfo will get address information for the host specified by hostnae */
  int rv = getaddrinfo(hostname, port, &hints, &results);

  if (rv != 0){
    err_msg_die("getaddrinfo: %s\n", gai_strerror(rv));
  }

  return results;
}

/*
 * The function open_connection create socket and establishes a connection to the server
*/

int open_connection(struct addrinfo* addr_list){

  struct addrinfo* addressInfo;
  int sockfd, connectfd;

  /* Iterate through each addr info in the list; Stop when we successully connect to one */
  for (addressInfo = addr_list; addressInfo != NULL; addressInfo = addressInfo->ai_next)
    {
      sockfd = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	  
      /* Try the next address since the socket operation failed */
	  
      if (sockfd == -1){
        continue;
		}
      connectfd = connect(sockfd,addressInfo->ai_addr, addressInfo->ai_addrlen);
	  
       /* Stop iterating of we are able to connect to the server */
      if ( connectfd != -1){
        break;
		}
	}

  freeaddrinfo(addr_list);

  if (sockfd == -1){
    err_msg_die("Unable to create socket");
  }
  if (connectfd == -1) {
    err_msg_die("Unable to connect");
  }

  return sockfd;
}
