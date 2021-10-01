#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

//  OUR SIMPLE LIST DATATYPE - A DATA ITEM, AND A POINTER TO ANOTHER LIST
typedef struct _list {
     char           *string;
     char           *hash;
     int            size;
     struct _list   *next;
} LIST;

// DECLARE GLOBAL FUNCTIONS
extern char *strSHA2(char *filename);

//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN list.c :

//  'CREATE' A NEW, EMPTY LIST
extern	LIST	*list_new(void);

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
extern	LIST	*list_add(LIST *, char *, char *);

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
extern	bool	 list_find (LIST *, char *, char *);

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
extern	void	 list_print(LIST *);

//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef	LIST * HASHTABLE;

//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN hashtable.c :

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern	HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *, char *);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *);
