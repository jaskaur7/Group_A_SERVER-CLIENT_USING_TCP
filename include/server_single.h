/** @file server_single.h
  */
#ifndef _SERVER_SINGLE_H_
#define _SERVER_SINGLE_H_

/* Including all Dependencies */
#include "common.h"

/**
* \function: short socket_create(int af_net, int sock_strem)
*
* \autor: Saksham Mal
*
* \brief:  The function is used to create a socket and once it is created it has to specify the domain and type of socket. The function returns an entry as small integer into file descriptor table and it  
*          returns -1 if it could not create socket.
*
* @param[in] domain It is the address domain of the socket. 
* @param[in] type It is the type of the socket provided. Here TCP which is a stream socket is used as it can communicate as a continuous stream of characters and is reliable.
*
*/

short socket_create(int af_net, int sock_strem){
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(af_net, sock_strem, 0);
    if (hSocket == -1){
      err_msg_die("Could not create socket");
    }
    return hSocket;
}


/**
* \fn: int bind_created_socket (int hSocket, int port)
*
* \author: Jaspreet Kaur(jaskaur7)
*
* \brief: This function will bind the socket with the local protocol address.
*
* The function takes two arguments hsocket and port number. The hsocket will be created by the function SocketCreate() with AF_INET protocol address and SOCK_STREAM, which is a type of network socket or interprocess communication socket that provides connection-oriented services without any limit and organized mechanisms for opening and closing of the connection. 
* The port number will either be entered manually while executing the program with '-p' followed by port number. The function will return 0 for success and -1 for any error. 
*
* @param[in] int hsocket: Socket descriptor of type integer. 
* @param[in] int port: Port number of integer type.
*
* \return: -1 if the socket bind is failed and 0 for success.
*
*/

int bind_created_socket(int hSocket, int port)
{
    int iRetval=-1;
    struct sockaddr_in  remote= {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(port); /* Local port */
    printf("binding the created socket\n");
    iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
    if (iRetval < 0){
      /*print the error message*/
      err_msg_die("bind failed.");
    }
    return iRetval;
}

#endif
