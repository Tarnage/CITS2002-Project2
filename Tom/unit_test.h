#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 50

extern void test(char*, char*, bool);

extern void test_string(char*, char*, char*);

extern void test_NULL(char*, void*);

extern void test_int(char*, char*, int, int);

extern void test_bool(char*, char*, bool, bool);

extern void print_summary();