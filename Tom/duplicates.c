#include <stdio.h>
#include <stdlib.h>

#include "duplicates.h"

void usage(char *progname, int opt) {
   //fprintf(stderr, USAGE_FMT, progname);
   printf ("Usage: %s [OPTION]... [FILE]...\n", progname);

      fputs (("\
Locate and report duplicate files in, and below, a named directory.\n\
\n\
"), stdout);

      fputs (("\
  -a,       do not ignore entries starting with .\n\
\n\
  -A,       advanced mode\n\
\n\
  -f,       find and list, one per line, the relative pathnames of all files whose SHA2\n\
            hash matches that of the indicated file. The name of the indicated file is not listed.\n\
            duplicates -f terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise\n\
\n\
  -h,       find and list, one per line, the relative pathnames of all files with the indicated SHA2 hash.\n\
            duplicates -h terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise.\n\
\n\
  -l,       duplicates lists all duplicate files found. Each line of output consists of the relative pathnames of two or more files\n\
            that are duplicates of each other. The pathnames of duplicate files (on the same line line) must be separated by the TAB character.\n\
\n\
  -m,       duplicates minimizes the total number of bytes required to store all files' data by modifying the directory structure being considered.\n\
\n\
  -q,       duplicates executes quietly, simply testing if the named directory contains any duplicate files.\n\
            duplicates -q produces no output at all, simply terminating with EXIT_SUCCESS if there are no duplicates\n\
            (i.e. storage is already minimized), or with EXIT_FAILURE otherwise.\n\
\n\
"), stdout);

   exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc < 2) {
        usage(argv[0], -1);
        exit(EXIT_FAILURE);
    }
    else {

//  TERMINATE PROGRAM, INDICATING SUCCESS
        exit(EXIT_SUCCESS);
    }
    return 0;
}
