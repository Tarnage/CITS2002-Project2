#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "duplicates.h"
#include "unit_test.h"


void test_dir_scan()
{   
    scan_directory(".");
}


int main(int argc, char *argv[])
{   
    test_dir_scan();
    print_dir_summary();
    list_all_files();
    exit(EXIT_SUCCESS);

    return 0;
}
