#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "unit_test.h"

/* Variable defined here */
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


void test_NULL(char name[], void *actual)
{
    bool pass = false;
    if(actual == NULL)pass = true;

    test(name, NULL, pass);

    if(!pass){
        printf("\tExpected %p got %p\n", NULL, actual);
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


void test_bool(char name[], char testName[], bool actual, bool expected)
{
    bool pass = false;
    if(actual == expected) pass = true;

    test(name, testName, pass);

    if(!pass){
        printf("\tExpected %s got %s\n", expected ? "true":"false", actual ? "true":"false");
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