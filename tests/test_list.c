#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "duplicates.h"
#include "unit_test.h"


void test_list_add()
{   
    LIST *test_list2 = {"Test2", "Hash2", 0, NULL};
    LIST *test_list1 = {"Test1", "Hash1", 0, test_list2};
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
