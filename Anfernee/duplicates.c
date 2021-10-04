#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

#include "duplicates.h"

// GLOBALs
bool ignore_mode = true;
bool quiet_mode  = false;



void usage(char *progname) {
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


void quiet_mode_summary()
{   
    // IF nbytes DOES NOT EQUAL ubytes WE HAVE DUPLICATES
    if(nbytes != ubytes){
        printf("DUPLICATES FILES FOUND\n");
        exit(EXIT_FAILURE);
    }
    printf("SUCCESS\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc > 3) {
        usage(argv[0]);
    }
    else {

    int		opt;

//  PROCESS COMMAND-LINE OPTIONS
    opterr	= 0;
    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {
            case 'a':
                printf("Option [-a] was selected\n");
                ignore_mode = false;
                break;
            case 'A':
                printf("Option [-A] was selected\n");
                break;
            case 'f':
                printf("Option [-f] was selected\n");
                break;
            case 'l':
                printf("Option [-l] was selected\n");
                break;
            case 'm':
                printf("Option [-m] was selected\n");
                break;
            case 'q':
                printf("Option [-q] was selected\n");
                quiet_mode = true;
                break;
            default: /* '?' */
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
//  INITIALIZE HASHTABLE FOR CHECKING DUPLICATES
    HASHTABLE   *hash_table = hashtable_new();

    //scan_directory(".");
    //scan_dir_recur("/mnt/d/Github/CITS2002-Project2/tests");
    //scan_dir_recur("/mnt/d/Github/CITS2002-Project2/Tom");
    scan_dir_recur("/mnt/d/University Documents/UWA/2021/Semester 2/CITS2002/Project-2/CITS2002-Project2/Anfernee");
//  ADD ALL FILES TO hash_table TO CHECK FOR DUPLICATES
    for(int i = 0; i < nfiles; ++i){
        hashtable_add(hash_table, files);
        ++files;
    }

    //hashtable_print(hash_table);

    //ubytes = nbytes - hashtable_count_dupes(hash_table);
    
    //ufiles = nfiles - ufiles;
   
    hashtable_count_dupes(hash_table);
// MORE COMMENTS TO COME
//  PRINT SUMMARY IFF quiet_mode = false
    if( quiet_mode ){
        quiet_mode_summary();
    }
    else{
        print_dir_summary();
    }
//  TERMINATE PROGRAM, INDICATING SUCCESS
        exit(EXIT_SUCCESS);
    }
    return 0;
}
