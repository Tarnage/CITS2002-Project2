#ifndef DUPLICATES_H
#define DUPLICATES_H
#include <stdbool.h>
#include <stdint.h>
#include "structures.h"
#include "list.h"
#include "strSHA2.h"
#include "hashtable.h"

//  DEFINE OPTLIST HERE
#define	OPTLIST		"f:h:aAlmq"

#ifndef STRCMP
#define STRCMP(p, q)   (strcmp(p, q) == 0)
#endif

// OPTION MODES DEFINED IN duplicates.c
bool           ignore_mode;

// OPTION -f
bool           find_file_mode;
char          *wanted_file;
char          *wanted_pathname;
char          *wanted_file_hash;
bool           w_file_found;



//OPTION -h
int            found_hash_count;

// STORES ALL FILES IN GIVEN DIRECTORY 
FILES         *files; 
//------------------------------------------------------------------------------------------------
// COUNTERS FOR DEFAULT SUMMARY 

int             nfiles;  // nfiles incremented in read_dir.c
int             nbytes;  // nbytes incremented in read_dir.c
int             ufiles;  // ufiles calculated in duplicates.c
int             ubytes;  // ubytes calculated in duplicates.c
int             file_count;  // file_count incremented in read_dir.c


// -----------------------------------------------------------------------------------------------

// SCANS DIRECTORY RECURSIVELY 
extern      void      scan_dir_recur(char *);

// FIND DUPLICATES
extern      void      find_duplicates(LIST *);

// DETERMINE IF FILE IS A DUPLICATE
extern    void        count_duplicates(HASHTABLE *);

// SCANS DIRECTORY RECURSIVELY 
extern      bool      file_ignored(const char *);

// PRINTS ALL FILES FOUND
extern      void      list_all_files(void);

// PRINT DUPES
extern      void      print_dupes(LIST *list);


// -----------------------------------------------------------------------------------------------

#endif
