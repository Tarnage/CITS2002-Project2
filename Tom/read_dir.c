#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <sys/param.h>
#include  <string.h>


#include "duplicates.h"

#if     defined(__linux__)
extern         char *strdup(const char *s);
#endif

#ifndef STRCMP
#define STRCMP(p, q)   strcmp(p, q) == 0
#endif

FILES           *files  = NULL;
//  FILE IS IGNORED IF TRUE AND FILE (.) MEANING ITS A HIDDEN FILE

bool file_ignored(const char *name)
{   
    return (ignore_mode && (name[0] == '.'));
}

//  SCANS DIRECTORY RECURSIVELY 
void scan_dir_recur(char *dirname)
{
    DIR             *dirp;
    struct dirent   *dp;

    //  ENSURE THAT WE CAN OPEN (read-only) THE REQUIRED DIRECTORY
    dirp       = opendir(dirname);
    
    if (dirp == NULL) 
    {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

    // STORE CURRENT WORKING PATH
    // NEEDED TO CORRECTLY IDENITFY SUB-DIRECTORIES
    // char            current_path[MAXPATHLEN];
    // if((getcwd(current_path, MAXPATHLEN)) == NULL)
    //     exit(EXIT_FAILURE);
    

    //  READ FROM THE REQUIRED DIRECTORY, UNTIL WE REACH ITS END
    while((dp = readdir(dirp)) != NULL) 
    {
        struct stat     stat_info;
        char            pathname[MAXPATHLEN];

        //  SENDS FORMATTED STRING TO STRING POINTER POINTED BY pathname
        sprintf(pathname, "%s/%s", dirname, dp->d_name);

        //  DETERMINE ATTRIBUTES OF THIS DIRECTORY ENTRY
        if(stat(pathname, &stat_info) != 0) 
        {
            perror( pathname );
            exit(EXIT_FAILURE);
        }

        //  CHECKS IF FILE IS A DIRECTORY AND RECURSIVELY READS FILES 
        if( S_ISDIR(stat_info.st_mode) 
            && (!STRCMP(dp->d_name, ".")) 
            && (!STRCMP(dp->d_name, "..")) )
        {
            scan_dir_recur(pathname);
        }

        else if ( !file_ignored(dp->d_name) 
                   && (!STRCMP(dp->d_name, ".") 
                   && !STRCMP(dp->d_name, "..")) )
        {

            //  EXTEND OUR ARRAY OF STRUCTURES BY ONE ELEMENT
            files = realloc(files, (nfiles+1)*sizeof(files[0]));
            CHECK_ALLOC(files);			// ensure allocation was OK

            //  REMEMBER (COPY) THIS ELEMENT'S RELATIVE PATHNAME
            files[nfiles].pathname  = strdup(pathname);
            CHECK_ALLOC(files[nfiles].pathname);	          // ensure allocation was OK
            files[nfiles].filename  = strdup(dp->d_name);
            CHECK_ALLOC(files[nfiles].filename);

            //  REMEMBER THIS ELEMENT'S MODIFICATION TIME
            files[nfiles].mtime     = stat_info.st_mtime;     // TODO maybe wont need this
            files[nfiles].bytesize  = stat_info.st_size;      // its byte size
            //nbytes                 += stat_info.st_size;      // add to total bytes so far
            

            //  DO A CHECK IF WE ARE IN find_file_mode
            if( find_file_mode )
            {
                // IF CURRENT FILE IS wanted_file and we havent file a file yet COPY ITS SHA2
                if( STRCMP(dp->d_name, wanted_file) && !w_file_found)
                {   
                    wanted_file_hash = strdup( strSHA2(pathname) ); // IF WE FIND THE FILE SAVE ITS HASH
                    wanted_pathname = files[nfiles].pathname;       // AND SAVE ITS ABSOLUTE PATH NAME
                    w_file_found = true;
                }
            }

            ++nfiles;
        }
    }
    
    //  CLOSE THE DIRECTORY
    closedir(dirp);
}

void list_all_files()
{
    for(int n=0 ; n<nfiles ; ++n) 
    {
        char *english = ctime(&files[n].mtime);

        english[24] = '\0';		// remove pesky trailing newline
        printf( "%s\t%i\t%s\n", english, files[n].bytesize, files[n].pathname );
    }
}
