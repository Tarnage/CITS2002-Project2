#ifndef LIST_H
#define LIST_H
#include "structures.h"
#include <stdbool.h>
//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define   CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }
// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN list.c :

//  'CREATE' A NEW, EMPTY LIST
extern	  LIST	     *list_new(void);

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
extern	  LIST	     *list_add(LIST *, FILES *);

//  APPENDS DUPLICATES TO LIST OF LISTS
extern	  void 	     list_find_dupe(LIST *);

//  DETERMINE IF A REQUIRED ITEM (A FILE) IS STORED IN A GIVEN LIST
extern    bool       list_find(LIST *, char *);

//  DETERMINE IF A REQUIRED HASH (OF A FILE) IS STORED IN A GIVEN LIST
extern    bool       list_find_hash(LIST *, char *);

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
extern	  void	     list_print(LIST *);

// GLOBAL VARIABLES 
LIST           **dupes;

#endif