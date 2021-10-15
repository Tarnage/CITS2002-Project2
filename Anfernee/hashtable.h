#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "structures.h"

//  RESEARCH SHOWS THAT USING PRIME-NUMBERS CAN IMPROVE PERFORMANCE
//  c.f.  https://www.quora.com/Why-should-the-size-of-a-hash-table-be-a-prime-number
#define	HASHTABLE_SIZE		2551

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

//  DETERMINE IF A REQUIRED HASH (OF A FILE) IS STORED IN A GIVEN LIST
extern	  bool		 hashtable_find_hash(HASHTABLE *, char *);

//  PRINTS HASHTABLE CONTENTS WITH GIVEN SHA2
extern    void       hashtable_print_hash(HASHTABLE *, char *);

//  PRINTS HASHTABLE CONTENTS
extern    void       hashtable_print_all(HASHTABLE *);

// ADDED FOR TESTING CAN REMOVE 
extern    uint32_t   hash_string(char *);
#endif
