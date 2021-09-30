#include <stdio.h>
#include <stdlib.h>

#include "duplicates.h"

int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc < 2) {
        fprintf(stderr, "Usage: %s argument\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
//  CALL THE PROCESS FUNCTION AND COLLECT THE RESULT
        int answer = process_argument(argv[1]);

//  PRINT THE RESULT
        printf("The answer is %d\n", answer);

//  TERMINATE PROGRAM, INDICATING SUCCESS
        exit(EXIT_SUCCESS);
    }
    return 0;
}