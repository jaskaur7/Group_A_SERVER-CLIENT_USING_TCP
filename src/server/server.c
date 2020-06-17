#include "common.h"

/* Socket Creation */

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
