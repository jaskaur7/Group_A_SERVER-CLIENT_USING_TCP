/*    Including Dependencies     */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "../../include/server_single.h"
#include "../../include/server_multi.h"
#include "../../include/common.h"

/* redefine assert to set a boolean flag */
#ifdef assert
#undef assert
#endif
#define assert(x) (rslt = rslt && (x))


/* main result return code used by redefined assert */
static int rslt;

/* variables controling stub functions */
static int expected_code;
static int should_exit;
static jmp_buf jump_env;

/* test suite main variables */
static int done;
static int num_tests;
static int tests_passed;



/**
* \fn: void TestStart(char *name)
*
* \author: Hitin Sarin
*
* \brief: This is the utility function for starting testing of our functions
*
*/ 

void TestStart(char *name)
{
    num_tests++;
    rslt = 1;
    printf("-- Testing %s ... ",name);
}


/**
* \fn: void TestEnd()
*
* \author: Hitin Sarin
*
* \brief: This is the utility function for ending testing of our functions
*
*/ 

void TestEnd()
{
    if (rslt) tests_passed++;
    printf("%s\n", rslt ? "success" : "fail");
}


/* Test Case For Socket_Creation */

/**
* \fn: int test_normal_socket_create(int af_net, int sock_stream)
*
* \author: Hitin Sarin
*
* \brief: This is the test function where we will test the socket_creation which was implemented in the Assignment.
*
* The function takes the below arguments and shows when all the correct argument are given, the test passes stating the "Socket is Created". When in the main function  int sockfd = test_normal_socket_create(AF_INET , SOCK_STREAM); is called it passes successfully.
*
* @param[in] domain: Type of Internet family used in the socket creation. (AF_INET)
* @param[in] type: Type of communication used in the socket creation within the above-mentioned domain. (SOCK_STREAM)
* @param[in] protocol: It specifies the protocol used in the socket creation. (Default=0)
*
* \return User_Type: non-zero value for success or -1 for failure.
*
*/ 


int test_normal_socket_create(int af_net, int sock_stream){
    int jmp_rval;
    int sockfd;

    TestStart("test_normal_socket_create");
    should_exit = 0;
    if (!(jmp_rval=setjmp(jump_env))){
        sockfd = socket_create(af_net, sock_stream);
    }

    assert(jmp_rval==0);
    assert(sockfd!=-1);
    TestEnd();
    return sockfd;
}







/**
* \fn: test_bind_created_socket(int hSocket, int port)
*
* \author: Jaspreet Kaur (jaskaur7)
*
* For this test case, the value of hsocket is coming from the test_normal_socket_create() function with AF_INET as protocol address and SOCK_STREAM as data stream.
* The port number passed from main function is 8000. It will return 0 for successful bind with "bind done" message.
*
* \return User_Type: 0 for success.
*
*/

void test_bind_created_socket(int hSocket, int port)
{
    int jmp_rval;
    int iRetval;

    TestStart("test_normal_open_connection");
    should_exit = 0;
    if (!(jmp_rval=setjmp(jump_env))){
        iRetval= bind_created_socket(hSocket, port);
    }

    assert(jmp_rval==0);
    assert(iRetval!=1);
    TestEnd();
}





/**
* function: void test_clientProcessing(int confd)
*
* author: Saksham Mal
*
* brief:  The function is used for testing whether there is no connection established or not which is then *             used by function connectionHandler to connect the client.
*
* @param[in] int 
* 
* return : it returns int value.
*
*/


void test_clientProcessing(int confd)
{
    int jmp_rval;
    int iRetval;

    TestStart("test_clientProcessing it should produce exception");
    should_exit = 0;
    if (!(jmp_rval=setjmp(jump_env))){
        iRetval= clientProcessing(confd);
    }

    assert(jmp_rval==0);
    assert(iRetval!=1);
    TestEnd();
}


/**
* function: int main(int argc, char *argv[])
*
* author: Saksham Mal
*
* brief:  The function is used for testing of all the test cases and returns the test cases passed.
*
*/


int main(int argc, char *argv[])
{
    num_tests = 0;
    tests_passed = 0;
    done = 0;

    /*Create socket */
    int sockfd_ = test_normal_socket_create(5 , 6);
    int sockfd = test_normal_socket_create(AF_INET , SOCK_STREAM);

    /*Bind*/
    test_bind_created_socket(sockfd, 8000);

    /*clientProcessing*/
    test_clientProcessing(0);

    printf("Total tests passed: %d\n", tests_passed);
    printf("Total tests faile: %d\n", num_tests - tests_passed);
    done = 1;
    return !(tests_passed == num_tests);
}
