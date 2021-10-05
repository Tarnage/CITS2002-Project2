//#include <dirent.h>
//#include <sys/types.h>
//#include <errno.h>
//#include <sys/stat.h>
#ifndef DUPLICATES_H
#define DUPLICATES_H
#include "structures.h"
#include "globals.h"
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

//  DEFINE OPTLIST HERE
#define	OPTLIST		"aAfhlmq"

// DEFINED in duplicates.c
bool           ignore_mode;
bool           quiet_mode;
bool           list_dupes;

// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN read_dir.c :

// READS DIRECTORY AND START COUNTS
extern    void      scan_directory(char *);

// SCANS DIRECTORY RECURSIVELY 
extern    void      scan_dir_recur(char *);

// SCANS DIRECTORY RECURSIVELY 
extern    bool      file_ignored(const char *);

// PRINTS SUMMARY OF THE FILES FOUND
extern    void      print_dir_summary(void);

// PRINTS ALL FILES FOUND
extern    void      list_all_files(void);


// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN duplicates.c :

extern    void      quiet_mode_summary(void);

//  PRINT EACH DUPE (THE RELATIVE PATHNAME) IN A GIVEN LIST TO stdout
extern    void      print_dupes(LIST *);
#endif
