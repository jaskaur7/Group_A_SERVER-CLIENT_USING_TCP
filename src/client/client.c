/**
*\fn: int main(int argc, char *argv[])
*
*\author:Prerit Sikerwal
*
*\brief:In this function, all the functions related to the working of client end such as creating & binding socket, connection to remote server and transfer of data string will be called.
*
*@param[in]:int argc, char *argv []
*
*/



#include "../../include/client.h"

/* Main ========================================================= */
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
  struct addrinfo* results = get_sockaddr(hints, argv[1], argv[2]);
  sockfd= open_connection(results);
  
  if (sockfd == -1){
    return EXIT_FAILURE;
  }
  printf ("Socket created and connected to port %s and hostname %s\n\n", argv[2], argv[1]);

  printf("Give me a String to send to the server: ");
  fgets(sendBuff, sizeof(sendBuff), stdin);
  
  /*Send the scanned input to the server through socket*/
  if (send (sockfd, sendBuff, strlen(sendBuff), 0) < 0){
    err_msg_die("send error");
  }

  /*Receive a reply from the server*/
  if ((read_in = recv(sockfd , recvBuff , MAXLINE-1 , 0)) < 0){
    err_msg_die("read error");
  }
  
  printf("The String recieved back from the server : %s",recvBuff);
  /*Closing the connection */
  close (sockfd);
  return 0;
}
