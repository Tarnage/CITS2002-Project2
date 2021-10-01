#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "duplicates.h"
#include "unit_test.h"

LIST *test_list;
LIST *test_empty;

char *test_name1 = "Test1";
char *test_hash1 = "Hash1";
int   test_size1 = 69;

char *test_name2 = "Test2";
char *test_hash2 = "Hash2";
int   test_size2 = 1223;

char *test_name3 = "Test3";
char *test_hash3 = "Hash3";
int   test_size3 = 1028466548;

void test_list_NULL()
{   
    test_NULL("Empty List:\t", test_list);
}

void test_list_add()
{   
    test_list = list_add(test_list, test_name1, test_hash1, test_size1);
    test_string("First name:\t", test_list->fname, test_name1);
    test_string("First hash:\t", test_list->fhash, test_hash1);
    test_int   ("First size:\t", "69", test_list->fsize, test_size1);

    test_list = list_add(test_list, test_name2, test_hash2, test_size2);
    test_string("Second name:\t", test_list->fname, test_name2);
    test_string("Second hash:\t", test_list->fhash, test_hash2);
    test_int   ("Second size:\t", "1223", test_list->fsize, test_size2);
}


void test_list_find()
{   
    test_bool("NULL list:\t", "", list_find(test_empty, test_name1, test_hash1, test_size1), false);
    test_bool("Find First:\t", "", list_find(test_list, test_name1, test_hash1, test_size1), true);
    test_bool("Does Not Exist:\t", "", list_find(test_list, test_name3, test_hash3, test_size3), false);
    test_bool("Find Second:\t", "", list_find(test_list, test_name2, test_hash2, test_size2), true);
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
        test_list = list_new();
        test_empty = list_new();

        printf("TESTING NULL\n");
        test_list_NULL();
        printf("TESTING ADD\n");
        test_list_add();
        printf("TESTING_FIND\n");
        test_list_find();

        print_summary();
        list_print(test_list);

        exit(EXIT_SUCCESS);
    }
    return 0;
}
