#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "structures.h"

//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef	LIST * HASHTABLE;

// -----------------------------------------------------------------------------------------------
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN hashtable.c :

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern	  HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	  void		 hashtable_add( HASHTABLE *, FILES *);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	  bool		 hashtable_find(HASHTABLE *, char *);

// DETERMINE IF FILE IS A DUPLICATE
extern    void       hashtable_count_dupes(HASHTABLE *);

//  PRINTS HASHTABLE CONTENTS
extern    void       hashtable_print(HASHTABLE *);

// ADDED FOR TESTING CAN REMOVE 
extern    uint32_t   hash_string(char *);
#endif