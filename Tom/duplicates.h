//#include <dirent.h>
//#include <sys/types.h>
//#include <errno.h>
//#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

// -----------------------------------------------------------------------------------------------
// DEFINED TYPEDEFS

// DATA TYPE FOR READING IN FILES
typedef struct _files{
    char           *pathname;
    char           *hash;
    int             bytesize;
    time_t          mtime;
} FILES;

//  OUR SIMPLE LIST DATATYPE - A DATA ITEM, AND A POINTER TO ANOTHER LIST
// TODO mayb a list that holds a pointer to a stat struct or files struct
typedef struct _list {
     FILES          *file_stats;
     struct _list   *next;
} LIST;


// -----------------------------------------------------------------------------------------------
// DECLARE GLOBAL VARIABLES

// DEFINED IN read_dir.c
// TODO maybe define in duplicates.c instead? because we may need access to hashtable to check for dupes
FILES          *files;   // array of found files
int             nfiles;  // nfiles incremented in read_dir.c
int             nbytes;  // nbytes incremented in read_dir.c
int             ufiles;  // ufiles calculated in duplicates.c
int             ubytes;  // ubytes calculated in duplicates.c

// -----------------------------------------------------------------------------------------------

//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef	LIST * HASHTABLE;

// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN strSHA2.c :

// DECLARE GLOBAL FUNCTIONS
extern    char      *strSHA2(char *);

// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN list.c :

//  'CREATE' A NEW, EMPTY LIST
extern	LIST	     *list_new(void);

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
extern	LIST	     *list_add(LIST *, FILES *);

//  DETERMINE IF A REQUIRED ITEM (A FILES STRUCT) IS DUPLICATE
extern	bool	     list_find_dupe(LIST *, FILES *);

//  DETERMINE IF A REQUIRED ITEM (A FILE) IS STORED IN A GIVEN LIST
extern    bool      list_find(LIST *list, char *);

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
extern	void	     list_print(LIST *);

// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN hashtable.c :

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern	HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *, FILES *);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *);

// DETERMINE IF FILE IS A DUPLICATE
extern    bool       hashtable_isDupe(HASHTABLE *, FILES *);

//  PRINTS HASHTABLE CONTENTS
extern    void       hashtable_print(HASHTABLE *);

// ADDED FOR TESTING CAN REMOVE 
extern    uint32_t   hash_string(char *);

// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN read_dir.c :

// READS DIRECTORY AND START COUNTS
extern    void scan_directory(char *);

// PRINTS SUMMARY OF THE FILES FOUND
extern    void print_dir_summary(void);

// PRINTS ALL FILES FOUND
extern    void list_all_files(void);
