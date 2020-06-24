/** @file common.h
  */
#ifndef _COMMON_H_
#define _COMMON_H_

/* Including all Dependencies */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <netdb.h>

#define MAXLINE 4096

/** @brief Function prototpes to give an error message
*
*
* This function is used to give an error message
*
*
*/
int err_msg_die(const char *fmt, ...);

#endif
