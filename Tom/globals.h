#ifndef GLOBALS_H
#define GLOBALS_H

#include "stdbool.h"
#include "structures.h"
// -----------------------------------------------------------------------------------------------
// DECLARE GLOBAL VARIABLES

// DEFINED IN read_dir.c
// TODO maybe define in duplicates.c instead? because we may need access to hashtable to check for dupes
FILES          *files;   // array of found files
int             nfiles;  // nfiles incremented in read_dir.c
int             nbytes;  // nbytes incremented in read_dir.c
int             ufiles;  // ufiles calculated in duplicates.c
int             ubytes;  // ubytes calculated in duplicates.c
int             dupe_count; // used to dynamically allocate **dupes
LIST           *found_hash;
int             found_hash_count; // defned in duplicates.c and incremented in list.c
bool            find_file_mode; // 
char           *find_me;
char           *find_me_hash;
#endif