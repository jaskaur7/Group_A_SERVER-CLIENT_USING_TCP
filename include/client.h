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