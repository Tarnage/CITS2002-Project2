#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "duplicates.h"
#include "unit_test.h"

HASHTABLE *test_hash_table;

char *test_name1 = "Test1";
int   test_size1 = 69;

char *test_name2 = "Test2";
int   test_size2 = 1223;

char *test_name3 = "Test3";
int   test_size3 = 1028466548;


void test_hash_add()
{   
    
    test_bool("Empty HashTable:\t", "", hashtable_find(test_hash_table, test_name1, test_size1), false);
    //hashtable_add(test_hash_table, test_name1, test_size1);
    //hashtable_find(test_hash_table, test_name1, test_size1);
}

int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc != 1) {
        fprintf(stderr, "Usage: %s argument\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        /*INITIALIZE pointer*/
        test_hash_table = hashtable_new();

        printf("TESTING ADD\n");
        test_hash_add();

        print_summary();

        exit(EXIT_SUCCESS);
    }
    return 0;
}
