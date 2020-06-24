#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "../../include/server_single.h"
#include "../../include/server_multi.h"
#include "../../include/common.h"

// redefine assert to set a boolean flag
#ifdef assert
#undef assert
#endif
#define assert(x) (rslt = rslt && (x))


// main result return code used by redefined assert
static int rslt;

// variables controling stub functions
static int expected_code;
static int should_exit;
static jmp_buf jump_env;

// test suite main variables
static int done;
static int num_tests;
static int tests_passed;

//  utility function
void TestStart(char *name)
{
    num_tests++;
    rslt = 1;
    printf("-- Testing %s ... ",name);
}

//  utility function
void TestEnd()
{
    if (rslt) tests_passed++;
    printf("%s\n", rslt ? "success" : "fail");
}

// test case
int test_normal_socket_create(int af_net, int sock_strem){
    int jmp_rval;
    int sockfd;

    TestStart("test_normal_socket_create");
    should_exit = 0;
    if (!(jmp_rval=setjmp(jump_env))){
        sockfd = socket_create(af_net, sock_strem);
    }

    assert(jmp_rval==0);
    assert(sockfd!=-1);
    TestEnd();
    return sockfd;
}

// test case
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


int main(int argc, char *argv[])
{
    num_tests = 0;
    tests_passed = 0;
    done = 0;
    /*Create socket */
    int sockfd_ = test_normal_socket_create(5 , 6);
    int sockfd = test_normal_socket_create(AF_INET , SOCK_STREAM);
    test_bind_created_socket(sockfd, 8000);
    test_clientProcessing(0);
    printf("Total tests passed: %d\n", tests_passed);
    printf("Total tests faile: %d\n", num_tests - tests_passed);
    done = 1;
    return !(tests_passed == num_tests);
}
