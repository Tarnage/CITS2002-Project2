#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
//#include <string.h>

#include "duplicates.h"

//  RESEARCH SHOWS THAT USING PRIME-NUMBERS CAN IMPROVE PERFORMANCE
//  c.f.  https://www.quora.com/Why-should-the-size-of-a-hash-table-be-a-prime-number
#define	HASHTABLE_SIZE		2551

//  --------------------------------------------------------------------

//  FUNCTION hash_string() ACCEPTS A STRING PARAMETER,
//  AND RETURNS AN UNSIGNED 32-BIT INTEGER AS ITS RESULT
//
//  see:  https://en.cppreference.com/w/c/types/integer

HASHTABLE *test_hash_table;

uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
HASHTABLE *hashtable_new(void)
{
    HASHTABLE   *new = malloc(HASHTABLE_SIZE * sizeof(LIST *));

    CHECK_ALLOC(new);

    return new;
}

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_add(HASHTABLE *hashtable, char *fname, int fsize)
{   
    // strSHA2 ONLY TAKES A VALID FILEPATH
    char *input_hash = strSHA2(fname);                          // hash the filename and use it to get the index if hash is the same the contents is the same
    uint32_t h   = hash_string(input_hash) % HASHTABLE_SIZE;    // thus, will be placed in the same index of a file with the same contents.
    hashtable[h] = list_add(hashtable[h], fname, input_hash, fsize);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find(HASHTABLE *hashtable, char *fname, int fsize)
{   
    // strSHA2 ONLY TAKES A VALID FILEPATH
    char *input_hash = strSHA2(fname);
    uint32_t h	= hash_string(input_hash) % HASHTABLE_SIZE;     // choose list
    
    return list_find(hashtable[h], fname, input_hash, fsize);
}