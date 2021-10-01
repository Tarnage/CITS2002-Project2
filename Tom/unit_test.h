#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 50

extern int numTest;
extern int numPass;

extern void test(char name[], char testName[], bool pass);

extern void test_string(char name[], char actual[], char expected[]);

extern void test_NULL(char name[], void *actual);

extern void test_int(char name[], char testName[], int actual, int expected);

extern void test_bool(char name[], char testName[], bool actual, bool expected);

extern void print_summary();