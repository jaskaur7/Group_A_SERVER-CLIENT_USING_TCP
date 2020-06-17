<<<<<<< HEAD
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
=======
/*This is the client main function and here, all the functions related to the working of client end such as creating & binding socket, connection to remote server and transfer of data string will be called.  */


int main(int argc, char *argv[]){

  char sendBuff[MAXLINE];
  char recvBuff[MAXLINE];
  struct sockaddr_in serv_addr;
  int read_in, sockfd;
  struct addrinfo hints;

  if(argc != 3){
    err_msg_die("\n Usage: %s hostname port number \n",argv[0]);
  }

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_INET;          /*Return socket address for the server's IPv4 addresses*/
  hints.ai_socktype = SOCK_STREAM;    /*Return TCP socket addresses*/
  struct addrinfo* results = get_sockaddr(argv[1], argv[2]);
  sockfd= open_connection(results);

  printf("Give me Something to send: ");
  fgets(sendBuff, sizeof(sendBuff), stdin);
  
  if (send (sockfd, sendBuff, strlen(sendBuff), 0) < 0){
    err_msg_die("send error");
  }

  /*Receive a reply from the server*/
  if ((read_in = recv(sockfd , recvBuff , MAXLINE-1 , 0)) < 0){
    err_msg_die("read error");
  }
  
  printf("%s",recvBuff);
  /*Closing the connection*/
  close (sockfd);
  return 0;
>>>>>>> a28f202927c80b64b8eecac02952b28edf75b12d
}
