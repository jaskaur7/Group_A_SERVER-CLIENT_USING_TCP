/** @file server_multi.h
 *  @brief Function prototypes for Multi-thread Server.
 *
 *  
 * This function is used to provide clientProcessing function to the multi-thread server main function.
 *
 */

#ifndef _SERVER_MULTI_H_
#define _SERVER_MULTI_H_

#include <pthread.h>
#include "common.h"

/**
* \function: int clientProcessing (int connfd)
*
* \authsor: Saksham Mal
*
* \brief:  The server receives data from the client, read the string and gives it back to the client and then closes the connection.
*
* @param[in] int The integer containing the connection status of the client.
*
* return: integer value for client disconnected and recieving failure.
*/

int clientProcessing (int connfd) {
    char recvBuff[MAXLINE];

    /*receive data from the client*/
    int numbytes = recv(connfd,recvBuff, sizeof(recvBuff)-1, 0);

    if(numbytes == 0){
    err_msg_die("Client disconnected");
    }
    if(numbytes == -1){
    err_msg_die("recv failed");
    }

    send(connfd, recvBuff, strlen(recvBuff),0); 
    close(connfd);
    return 0;
}

#endif
