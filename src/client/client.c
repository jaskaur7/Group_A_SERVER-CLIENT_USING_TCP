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
}
