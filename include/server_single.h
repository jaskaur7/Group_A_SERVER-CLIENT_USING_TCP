/** @file server_single.h
  */
#ifndef _SERVER_SINGLE_H_
#define _SERVER_SINGLE_H_

/* Including all Dependencies */
#include "common.h"

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
