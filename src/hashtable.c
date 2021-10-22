#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "duplicates.h"
#include "hashtable.h"
#include "list.h"
#include "strSHA2.h"

#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

//  --------------------------------------------------------------------

//  FUNCTION hash_string() ACCEPTS A STRING PARAMETER,
//  AND RETURNS AN UNSIGNED 32-BIT INTEGER AS ITS RESULT
uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') 
    {
        hash = hash*33 + *string;
        ++string;
    }

    return hash;
}

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
HASHTABLE *hashtable_new()
{
    HASHTABLE  *new = malloc(HASHTABLE_SIZE * sizeof(LIST *));

    CHECK_ALLOC(new);

    return new;
}

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_add(HASHTABLE *hashtable, FILES *file_stats)
{   
    // strSHA2 ONLY TAKES A VALID FILEPATH
    char *input_hash = strSHA2(file_stats->pathname);  // hash the file contents
    // copy the hash to file_stats 
    file_stats->hash = strdup(input_hash);
    uint32_t h   = hash_string(input_hash) % HASHTABLE_SIZE; // thus, will be placed in the same index of a file with the same contents.
    hashtable[h] = list_add(hashtable[h], file_stats); // add to a list
    nbytes += file_stats->bytesize; // increment the total number of bytes by the size of the file 

}

//  DETERMINE IF A FILE STRUCT ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find(HASHTABLE *hashtable, char *pathname)
{   
    // strSHA2 ONLY TAKES A VALID FILEPATH
    char *input_hash = strSHA2(pathname); // hash the file contents
    uint32_t h	= hash_string(input_hash) % HASHTABLE_SIZE;  // find index in hashtable

    return list_find(hashtable[h], pathname); // check if file with corresponding filename exists in list
}

//  DETERMINE IF A FILE STRUCT ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find_hash(HASHTABLE *hashtable, char *input_hash)
{   
    uint32_t h	= hash_string(input_hash) % HASHTABLE_SIZE;  // find index of hash
    
    return list_find_hash(hashtable[h], input_hash); // check if hash exists in the list 
}

//  PRINTS HASHTABLE CONTENTS WITH GIVEN SHA2
//  HELPER FUNCTION - NOT USED
void hashtable_print_hash(HASHTABLE *hashtable, char *input_hash)
{
    uint32_t h	= hash_string(input_hash) % HASHTABLE_SIZE; 
    list_print(hashtable[h]);
}

//  PRINTS HASHTABLE CONTENTS
//  HELPER FUNCTION - NOT USED
void hashtable_print_all(HASHTABLE *hashtable)
{
    for(int i = 0; i < HASHTABLE_SIZE; ++i)
    {
        list_print(hashtable[i]);
    }
}
