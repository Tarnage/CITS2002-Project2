#include <stdio.h>
#include <stdlib.h>

#include "duplicates.h"

int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc >= 2) {
        fprintf(stderr, "Usage: %s argument\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else {

//  TERMINATE PROGRAM, INDICATING SUCCESS
        exit(EXIT_SUCCESS);
    }
    return 0;
}
