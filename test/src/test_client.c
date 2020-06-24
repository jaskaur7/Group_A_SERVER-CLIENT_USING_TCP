/**
*\fn: TestStart(),TestEnd(),test_normal_open_connection(),int main()
*
*\author:Prerit Sikerwal
*
*\brief: These are few functions used for testing of client part of our project.A brief description  of each function is given ahead.
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "../../include/client.h"
#include "../../include/common.h"


#ifdef assert
#undef assert
#endif
#define assert(x) (rslt = rslt && (x))


/* main result return code used by redefined assert*/
static int rslt;

/* variables controling stub functions*/
static int expected_code;
static int should_exit;
static jmp_buf jump_env;

/* test suite main variables*/
static int done;
static int num_tests;
static int tests_passed;

/* utility function*/
void TestStart(char *name)
{
    num_tests++;
    rslt = 1;
    printf("-- Testing %s ... ",name);
}

/*  utility function*/
void TestEnd()
{
    if (rslt) tests_passed++;
    printf("%s\n", rslt ? "success" : "fail");
}

/* test case*/
void test_normal_open_connection(struct addrinfo* addr_list)
{
    int jmp_rval;
    int sockfd;

    TestStart("test_normal_open_connection");
    should_exit = 0;
    if (!(jmp_rval=setjmp(jump_env))){
        sockfd= open_connection(addr_list);
    }

    assert(jmp_rval==1);
    assert(sockfd!=1);
    TestEnd();
}

int main(int argc, char *argv[])
{	
    char hostbuffer[256];
    int host_name;
    num_tests = 0;
    tests_passed = 0;
    done = 0;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;          /*Return socket address for the server's IPv4 addresses*/
    hints.ai_socktype = SOCK_STREAM;    /*Return TCP socket addresses*/
    host_name = gethostname(hostbuffer, sizeof(hostbuffer));
    char* hostname = &hostbuffer[0]; 
    char* port = "8080"; 
    struct addrinfo* results = get_sockaddr(hints, hostname, port);
    test_normal_open_connection(results);
    printf("Total tests passed: %d\n", tests_passed);
    printf("Total tests faile: %d\n", num_tests - tests_passed);
    done = 1;
    return !(tests_passed == num_tests);
}
