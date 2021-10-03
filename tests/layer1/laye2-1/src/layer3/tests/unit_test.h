#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 50

int numTest;
int numPass;

extern void test(char name[], char testName[], bool pass);

extern void test_string(char name[], char actual[], char expected[]);

extern void test_NULL(char name[], char *actual);

extern void test_int(char name[], char testName[], int actual, int expected);

extern void print_summary();