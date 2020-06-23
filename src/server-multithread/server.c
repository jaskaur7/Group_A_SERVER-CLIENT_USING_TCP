
#include <pthread.h>
#include "../../include/queue.h"
#include "../../include/common.h"

/*Declare global variables*/
pthread_mutex_t mutex;
pthread_cond_t cond;

struct Queue* q;

struct inputVal {
  unsigned short port;
  int no_of_threads;
  int size_of_queue;
};


/**
* \fn: int socket_create(int af_net, int sock_strem, 0)
*
* \author: Hitin Sarin
*
* \brief: This function will create a socket on the server end.
*
* The function takes two arguments af_net and sock_stream arguments. 
*
* @param[in] int domain: Type of Internet family used in the socket creation. (AF_INET)
* @param[in] int type: Type of communication used in the socket creation within the above-mentioned domain (SOCK_STREAM)
* @param[in] int protocol: It specifies the protocol used in the socket creation. (Default - 0)
*
* \return: integer value hsocket for success or -1 for failure.
*
*/

short socket_create(void){
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == -1){
      err_msg_die("Could not create socket");
    }
    return hSocket;
}








/**
* \fn: int main(int argc, char *argv)
* 
* \author: Hitin Sarin
*
* \brief: This is the mutithreading server main function where other functions such as queue creation, socket creation, binding socket and connection handler to multipe remote clients will be executed.
*
* The function takes two arguments argc and argv arguments. The argc tells the number of arguments and argv tells the list of arguments.
*
* @param[in] int argc: Integer input for count of the arguments. 
* @param[in] char *argv: Character type pointer which points to list of passed values.
*
* \return: 0 for success or -1 for failure.
*
*/ 


int main(int argc, char **argv) {

  struct inputVal input_values;

  if(argc != 4){
    err_msg_die("\n Usage: %s  (port number) (no of threads) (size of queue)\n",argv[0]);
  }

  input_values.port = atoi(argv[1]);
  input_values.no_of_threads = atoi(argv[2]);
  input_values.size_of_queue = atoi(argv[3]);

  /* Create a Queue */
  q = createQueue(input_values.size_of_queue);

  /* Create socket */
  short socket_desc = socket_create();
  if (socket_desc == -1){
      err_msg_die("Could not create socket");
  }

  printf("Socket created\n");
  
  /* Binding the socket */
  if( bind_created_socket(socket_desc, input_values.port) < 0){
      //print the error message
      err_msg_die("bind failed.");
  }
    printf("bind done\n");

  /* Initialize the mutex global variable */
    pthread_mutex_init(&mutex,NULL);

   /* Declare the thread pool array */
    pthread_t threadPool[input_values.no_of_threads];

    /* Make Thread Pool */
    for(int i = 0; i < atoi(argv[2]); i++){
      pthread_create(&threadPool[i], NULL, connectionHandler, (void *) NULL);
    }

    listen(socket_desc, 3); 

    /* Accept connection and push them onto the stack */
    while(1){
        printf("\nMain thread is Accepting Connections\n");

        /* The accept call blocks until a connection is found
            * then the connection is pushed onto the queue by queue_add */
        queue_add(accept(socket_desc, (struct sockaddr*)NULL, NULL)); 

        printf("\n\nConnection Completed\n\n");
    }

    close(socket_desc);
    return 0;
}