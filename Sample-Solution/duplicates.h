#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

#define	AUTHOR_EMAIL	        "Chris.McDonald@uwa.edu.au"

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

//  --------------------------------------------------------------------

// DECLARE EXTERNAL FUNCTIONS
#if defined(__linux__)
extern	char		*strdup(const char *);
#endif

//  DEFINED IN directories.c
extern  int process_directory(char *dirname,
                              bool aflag, char *fflag, char *hflag, bool qflag);

//  DEFINED IN files.c
extern  int add_pathname(char *filename);

//  DEFINED IN listthings.c
extern  int  list_duplicates(void);
extern  void list_statistics(void);

#if	defined(ADVANCED)
//  DEFINED IN minimize.c
extern  int minimize_duplicates(void);
#endif

//  DEFINED IN strSHA2.c
extern  char *strSHA2(char *filename);

