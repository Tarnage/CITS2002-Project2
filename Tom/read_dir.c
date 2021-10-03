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
        if( (strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0) ){  
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
    }
//  CLOSE THE DIRECTORY
    closedir(dirp);
}

//  SCANS DIRECTORY RECURSIVELY 
void scan_dir_recur(char *dirname)
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

        // if((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0) ){
        //     printf("%i:\n", stat_info.st_mode);
        //     printf("%s:\n", dp->d_name);
        // }

        if( (strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0) ){  
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

//  CHECKS IF FILE IS A DIRECTORY AND RECURSIVELY READS FILES 
        if(S_ISDIR(stat_info.st_mode) && 
            strcmp(dp->d_name, ".") != 0 &&
                strcmp(dp->d_name, "..") != 0){
            scan_dir_recur(pathname);
        }
    }
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

void list_all_files(void)
{
    for(int n=0 ; n<nfiles ; ++n) {
        char *english = ctime(&files[n].mtime);

        english[24] = '\0';		// remove pesky trailing newline
        printf( "%s\t%i\t%s\n", english, files[n].bytesize, files[n].pathname );
    }
}


