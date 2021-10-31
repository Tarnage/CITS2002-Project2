#define _DEFAULT_SOURCE // only required to detect symbolic-links (not required)
#define _BSD_SOURCE	// only required to detect symbolic-links (not required)

#include "duplicates.h"
#include <sys/param.h>
#include <dirent.h>

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

static  int nduplicates = 0;

static void process_directory_recursively(char *dirname,
                            bool aflag, char *fflag, char *hflag, bool qflag)
{
//  ENSURE THAT WE CAN OPEN/READ THE DIRECTORY
    DIR *dirp	= opendir(dirname);

    if(dirp) {
        struct dirent	*dp;

//  READ EACH DIRECTORY ENTRY
	while((dp = readdir(dirp)) != NULL) {

//  ALWAYS IGNORE THIS DIRECTORY (dot) AND ITS PARENT (dotdot)
	    if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
		continue;
            }

//  IGNORE ALL OTHER 'DOT' FILES AND DIRECTORIES, UNLESS REQUESTED
	    if(aflag == false && dp->d_name[0] == '.') {
		continue;
            }

//  RECONSTRUCT THE PATHNAME <- dir+entry 
            char        fullpath[MAXPATHLEN];
	    sprintf(fullpath, "%s/%s", dirname, dp->d_name);

//  ENSURE THAT WE CAN GET THE ATTRIBUTES OF THIS PATHNAME
            struct stat statinfo;

	    if(stat(fullpath, &statinfo) != 0) {        // hmmm, silently ignore
		continue;
            }

//  (NOT REQUIRED) DETECTING AND IGNORING SYMBOLIC-LINKS
            struct stat lstatinfo;

	    if(lstat(fullpath, &lstatinfo) == 0  && S_ISLNK(lstatinfo.st_mode)) {
                fprintf(stderr, "(not required) ignoring SYMLINK   %s\n", fullpath);
                continue;
            }

//  IS THIS A REGULAR FILE?
	    if(S_ISREG(statinfo.st_mode)) {

//  JUST WANT FILES WITH MATCHING HASH?
                if(hflag) {
                    char *sha2 = strSHA2(fullpath);

                    if(sha2 && strcmp(sha2, hflag) == 0) {
                        ++nduplicates;

                        if(!qflag && ! (fflag && strcmp(fflag, fullpath) == 0)) {
                            printf("%s\n", fullpath);
                        }
                    }
                }
//  OTHERWISE, ADD TO THE COLLECTION OF PATHNAMES
                else {
                    nduplicates += add_pathname(fullpath);
                }
            }

//  ELSE, IS IT A DIRECTORY?  RECURSIVELY PROCESS DIRECTORY
	    else if(S_ISDIR(statinfo.st_mode)) {
		process_directory_recursively(fullpath, aflag, fflag, hflag, qflag);
            }

//  ALL OTHER TYPES OF DIRECTORY ENTRIES ARE IGNORED
	}
	closedir(dirp);
    }
}

int process_directory(char *dirname, bool aflag, char *fflag, char *hflag, bool qflag)
{
    nduplicates = 0;
    process_directory_recursively(dirname, aflag, fflag, hflag, qflag);
    return nduplicates;
}
