/** @file client.h
 *  @brief Function prototypes for Client end.
 *
 *  
 * This function is used to provide get_sockaddr and open_connection function to the client's main function.
 *
 */

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "common.h"

/**
* \fn: get_sockaddr(struct addrinfo hints, const char* hostname, const char *port)
*
* \author: Hitin Sarin
*
* \brief: The function get_sockaddr converts the server's address and port into a form usable to create a socket.
*
* The function takes three arguments struct addrinfo hints, const char* hostname, const char *port.  
*
* @param[in] struct addrinfo hints: Address information for the host specified by hostname
* @param[in] const char* hostname: Hostname/IP Address of the machine to be connected
* @param[in] const char *port: Port at which connection will take place
*
* \return: 0 for success or non-zero for failure.
*
*/ 

struct addrinfo* get_sockaddr(struct addrinfo hints, const char* hostname, const char *port){
  
  struct addrinfo* results;
  /* Use getaddrinfo will get address information for the host specified by hostname */
  int rv = getaddrinfo(hostname, port, &hints, &results);

  if (rv != 0){
    err_msg_die("getaddrinfo: %s\n", gai_strerror(rv));
  }

  return results;
}













/**
*\fn:int open_connection(struct addrinfo* addr_list)
*
*\author: Prerit Sikerwal
*
*\brief:The client will establish a connection with server by calling this open_connection () function. Following TCP protocol this function connects the socket (described by sockfd – file descriptor) to the remote host server.
*
*@param[in]: sockfd ,addr_list
*
*/


int open_connection(struct addrinfo* addr_list){

  struct addrinfo* addressInfo;
  int sockfd, connectfd;

  /*Iterate through each addr info in the list; Stop when we successully connect to one*/
  for (addressInfo = addr_list; addressInfo != NULL; addressInfo = addressInfo->ai_next){
      sockfd = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
      /* Try the next address since the socket operation failed*/
      if (sockfd == -1) 
        continue;

      connectfd = connect(sockfd,addressInfo->ai_addr, addressInfo->ai_addrlen);
       /*Stop iterating of we are able to connect to the server*/
      if ( connectfd != -1) 
        break;
    }
    
  /*Free address info list*/
  freeaddrinfo(addr_list);

  if (sockfd == -1){
    err_msg_die("Unable to create socket");
  }
  if (connectfd == -1) {
    err_msg_die("Unable to connect");
  }

  return sockfd;
}

#endif

