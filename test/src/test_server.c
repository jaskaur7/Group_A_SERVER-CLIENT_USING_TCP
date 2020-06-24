/**
* function: void test_clientProcessing(int confd)
*
* autor: Saksham Mal
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
* autor: Saksham Mal
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
    test_bind_created_socket(sockfd, 8000);
    test_clientProcessing(0);
    printf("Total tests passed: %d\n", tests_passed);
    printf("Total tests faile: %d\n", num_tests - tests_passed);
    done = 1;
    return !(tests_passed == num_tests);
}
