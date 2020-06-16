#include "common.h"

short SocketCreate(int af_net, int sock_strem)
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(af_net, sock_strem, 0);
    if (hSocket == -1)
  {
      err_msg_die("Could not create socket");
  }
    return hSocket;
}
int BindCreatedSocket(int hSocket, int port)
{
    int iRetval=-1;
    struct sockaddr_in  remote= {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(port); /* Local port */
    iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
    if (iRetval < 0){
         
      //print the error message
      err_msg_die("bind failed.");
  
    }
    return iRetval;
}

int main(int argc, char **argv) {

  short sockfd;
  int confd, n, port, c;
  struct sockaddr_in client;
  char recvBuff[MAXLINE + 1];

 printf ("%d",MAXLINE);
  if(argc != 2){
    err_msg_die("\n Usage: %s  (port number) \n",argv[0]);
  }
  
  port = atoi(argv[1]);
  //Create socket
  sockfd = SocketCreate(AF_INET , SOCK_STREAM);
  
  //Bind
  BindCreatedSocket(sockfd, port);
  printf("bind done\n");

    if((listen(sockfd, 3))<0){
    err_msg_die("listen failed.");
    } 

     /*Accept connection */
    while(1)
    {
        printf("\nWaiting for connection\n");
        fflush(stdout);
        c = sizeof(struct sockaddr_in);
        confd = accept(sockfd, (struct sockaddr*)&client, (socklen_t*)&c); 
        if (confd < 0){
		    err_msg_die("accept failed");
	    }
        printf("\nConnection accepted\n");
        if ((recv(confd , recvBuff , MAXLINE-1, 0 )) < 0){
             err_msg_die("read error.");
    }
    send(confd, recvBuff, strlen(recvBuff),0); 
    close(confd);
    }
    
    close(sockfd);
  return 0;
}