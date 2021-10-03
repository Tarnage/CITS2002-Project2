#include  <stdio.h>
#include  <stdbool.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <sys/param.h>
#include  <time.h>
#include  <string.h>
#include  <getopt.h>

#include "duplicates.h"

#define	OPTLIST		"r"

#if     defined(__linux__)
extern         char *strdup(const char *s);
#endif


FILES           *files  = NULL;
// COUNT TOTAL NUMBER OF FILES FOUND
int             nfiles  = 0;
// TOTAL BYTES OF ALL FILES FOUND
int             nbytes  = 0;
// TOTAL NUMBER OF UNIQUE FILES
int             ufiles  = 0;
// TOTAL BYTES OF UNIQUE FILES
int             ubytes  = 0;


void scan_directory(char *dirname)
{
    DIR             *dirp;
    struct dirent   *dp;

//  ENSURE THAT WE CAN OPEN (read-only) THE REQUIRED DIRECTORY
    dirp       = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

//  READ FROM THE REQUIRED DIRECTORY, UNTIL WE REACH ITS END
    while((dp = readdir(dirp)) != NULL) {  
        struct stat     stat_info;
        char            pathname[MAXPATHLEN];

//  SENDS FORMATTED STRING TO STRING POINTER POINTED BY pathname
        sprintf(pathname, "%s/%s", dirname, dp->d_name);
        // FOR TESTING
        printf("%s/%s\n", dirname, dp->d_name);

//  DETERMINE ATTRIBUTES OF THIS DIRECTORY ENTRY
        if(stat(pathname, &stat_info) != 0) {
            perror( pathname );
            exit(EXIT_FAILURE);
        }

//  EXTEND OUR ARRAY OF STRUCTURES BY ONE ELEMENT
        files                   = realloc(files, (nfiles+1)*sizeof(files[0]));
	    CHECK_ALLOC(files);			// ensure allocation was OK

//  REMEMBER (COPY) THIS ELEMENT'S RELATIVE PATHNAME
        files[nfiles].pathname  = strdup(pathname);
	    CHECK_ALLOC(files[nfiles].pathname);	// ensure allocation was OK

//  REMEMBER THIS ELEMENT'S MODIFICATION TIME
        files[nfiles].mtime     = stat_info.st_mtime;     // TODO maybe wont need this
        files[nfiles].bytesize  = stat_info.st_size;      // its byte size
        nbytes                 += stat_info.st_size;      // add to total bytes so far
        ++nfiles;
    }

//  TODO ADD CHECK FOR UNIQUE FILES AND COUNT THE UNIQUE FILE. (THE USE OF HASH TABLE MIGHT BE THE SOLUTION)

//  CLOSE THE DIRECTORY
    closedir(dirp);
}

void print_dir_summary()
{
    printf("nfiles:\t%i\n", nfiles);
    printf("nbytes:\t%i\n", nbytes);
    printf("ufiles:\t%i\n", ufiles);
    printf("ubytes:\t%i\n", ubytes);
}


