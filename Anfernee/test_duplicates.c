#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "duplicates.h"

#define SIZE 50

int numTest = 0;
int numPass = 0;


void test(char name[], char testName[], bool pass)
{
    ++numTest;
    if(pass){
        ++numPass;
        printf("Pass: ");
    }
    else{
        printf("Fail: ");
    }
    printf("\t");
    printf("%s %s\n", name, testName);
}


void test_string(char name[], char actual[], char expected[])
{
    bool pass = false;
    if(strcmp(actual, expected) == 0)pass = true;

    test(name, expected, pass);

    if(!pass){
        printf("\tExpected %s got %s\n", expected, actual);
    }
}


void test_NULL(char name[], char *actual)
{
    bool pass = false;
    if(actual == NULL)pass = true;

    test(name, NULL, pass);

    if(!pass){
        printf("\tExpected %p got %s\n", NULL, actual);
    }
}


void test_int(char name[], char testName[], int actual, int expected)
{
    bool pass = false;
    if(actual == expected) pass = true;

    test(name, testName, pass);

    if(!pass){
        printf("\tExpected %i got %i\n", expected, actual);
    }

}


void print_summary()
{
    printf("\n");
    printf("Passed %i / %i tests\n", numPass, numTest);
    if(numPass == numTest){
        printf("All tests passed\n");
    }
    else{
        printf("%i TESTS FAILED\n", numTest-numPass);
    }
}


void test_list_add()
{   
    LIST *test_list1 = {"Test1", };
    LIST *test_list2 = {};
}


int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc != 1) {
        fprintf(stderr, "Usage: %s argument\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        
        example_test();
        print_summary();

        exit(EXIT_SUCCESS);
    }
    return 0;
}
