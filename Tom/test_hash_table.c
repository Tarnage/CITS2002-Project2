#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "duplicates.h"
#include "unit_test.h"

HASHTABLE *test_hash_table;

char *test_name1 = "strSHA2.c";
int   test_size1 = 69;

char *test_name2 = "unit_test.c";
int   test_size2 = 1223;

char *test_name3 = "read_directory.c";
int   test_size3 = 1028466548;

char *same_testname1 = "for_testing_hash.txt";
int   same_testsize1 = 69;


void test_hash_add()
{   
    test_bool("Empty HashTable:\t", "", hashtable_find(test_hash_table, test_name1, test_size1), false);

    hashtable_add(test_hash_table, test_name1, test_size1);
    test_bool("Added 1 element:\t", "", hashtable_find(test_hash_table, test_name1, test_size1), true);

    hashtable_add(test_hash_table, same_testname1, same_testsize1);
    test_bool("Added same file different content:\t", "", hashtable_find(test_hash_table, same_testname1, same_testsize1), true);
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

        //printf("%s\n", test_hash_table[0] == NULL ? "true":"false");
        //printf("%s\n", test_hash_table[1940] == NULL ? "true":"false");

        printf("TESTING ADD\n");
        test_hash_add();

        //print_summary();

        exit(EXIT_SUCCESS);
    }
    return 0;
}
