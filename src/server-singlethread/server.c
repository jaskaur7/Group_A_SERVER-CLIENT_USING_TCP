/** @file server.c
*
* Contains the main function for single_thread_server.
*
*/

#include "../../include/server_single.h"

/**
* \fn: int main(int argc, char **argv)
*
* \author: Jaspreet Kaur(jaskaur7)
*
* \brief: This is the main function where other functions will be called.
*
* The function takes two arguments argc and argv arguments. The argc tells the number of arguments and argv tells the list of arguments. 
*
* @param[in] int argc: Integer input for count of the arguments. 
* @param[in] char **argv: Character type pointer which points to list of passed values.
*
* \return User_Type: 0 for success or -1 for failure.
*
*/ 

int main(int argc, char **argv) {

    short sockfd;
    int confd, port, c, bind;
    struct sockaddr_in client;
    char recvBuff[MAXLINE + 1];

    if(argc != 2){
      err_msg_die("\n Usage: %s  (port number) \n",argv[0]);
    }
  
    port = atoi(argv[1]);
    /*Create socket */
    sockfd = socket_create(AF_INET , SOCK_STREAM);
    if (sockfd == -1){
      return 1;
    }
  
    /*Bind */
    bind = bind_created_socket(sockfd, port);
    if (bind == -1){
      return 1;
    }
    
    printf("bind done\n");
    
    if((listen(sockfd, 3))<0){
      err_msg_die("listen failed.");
    } 

    /*Accept connection */
    while(1){
      printf("\nWaiting for connection to be accepted\n");
      fflush(stdout);
      c = sizeof(struct sockaddr_in);
      confd = accept(sockfd, (struct sockaddr*)&client, (socklen_t*)&c); 
      
      if (confd < 0){
        err_msg_die("accept failed");
      }

      printf("\none Connection accepted\n");
      if((recv(confd , recvBuff , MAXLINE-1, 0 )) < 0){
        err_msg_die("read error.");
      } 
      
      /*Send the recieved data back to clinet */
      send(confd, recvBuff, strlen(recvBuff),0); 
      close(confd);
    }
    
  close(sockfd);
  return 0;
}
