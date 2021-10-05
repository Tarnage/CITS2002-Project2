#ifndef GLOBALS_H
#define GLOBALS_H
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
int            dupe_count;
#endif