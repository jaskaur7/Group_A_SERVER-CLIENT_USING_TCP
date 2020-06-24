
/**
* \fn: int err_msg_die(const char *fmt, ...)
*
* \author: Hitin Sarin
*
* \brief: Created a variadic function for error message included in Common header files.
*
* \return: success for non-zero, -1 for failure
*
*/

#include "../include/common.h"

int err_msg_die(const char *fmt, ...){
    int err_no;
    va_list ap;

    err_no = errno;

    va_start(ap,fmt);
    vfprintf(stdout,fmt,ap);
    fprintf(stdout,"\n");
    fflush(stdout);

    if (err_no != 0){
        fprintf(stdout,"(errno = %d) : %s\n", err_no, strerror(err_no));
        fprintf(stdout,"\n");
        fflush(stdout);
    }

    va_end(ap);

    return -1;
}
