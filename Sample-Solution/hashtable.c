#include "duplicates.h"
#include "hashtable.h"
#include <stdint.h>

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

HASHTABLE   **hashtable      = NULL;

static int  nfiles          = 0;
static int  nunique         = 0;

//  --------------------------------------------------------------------

//  DETERMINE IF A REQUIRED pathname IS STORED IN A GIVEN LIST

//  FOR THE BASIC VERSION OF THE PROJECT, EACH FILE'S PATHNAME IS STORED AND
//  COMPARED TO OTHER PATHNAMES WHEN STORING THEM UNIQUELY.  AS ONLY A SINGLE
//  DIRECTORY WILL BE EXAMINED, EACH PATHNAME BELOW THAT DIRECTORY IS UNIQUE.
//
//  FOR THE ADVANCED VERSION OF THE PROJECT, EACH FILE'S DEVICE AND INODE NUMBERS
//  ARE (ALSO) STORED IN CASE TWO OR MORE 'OVERLAPPING' DIRECTORIES ARE
//  PROVIDED ON THE COMMAND LINE.

#if defined(ADVANCED)
static bool pathlist_find(PATHLIST *pathlist, char *wanted_pathname, dev_t dev, ino_t ino)
#else
static bool pathlist_find(PATHLIST *pathlist, char *wanted_pathname)
#endif
{
    while(pathlist != NULL) {
#if defined(ADVANCED)
        if(pathlist->dev == dev && pathlist->ino == ino) {
#else
	if(strcmp(pathlist->pathname, wanted_pathname) == 0) {
#endif
	    return true;
        }
	pathlist	= pathlist->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW pathname, TESTING THAT ALLOCATION SUCCEEDS
static PATHLIST *pathlist_new_item(char *pathname)
{
    PATHLIST *new       = calloc(1, sizeof(PATHLIST) );
    CHECK_ALLOC(new);

    new->pathname       =  strdup(pathname);
    CHECK_ALLOC(new->pathname);
    ++nfiles;

    new->next           =  NULL;        // actually, the calloc() does this
    return new;
}

//  ADD A NEW pathname TO AN EXISTING PATHLIST
static PATHLIST *pathlist_add(PATHLIST *pathlist, char *pathname)
{
#if defined(ADVANCED)
    struct stat statinfo;

    stat(pathname, &statinfo);                  // it worked before!
    if(pathlist_find(pathlist, pathname, statinfo.st_dev, statinfo.st_ino)) {
        return pathlist;
    }
    else {
        PATHLIST *new   = pathlist_new_item(pathname);
        new->dev        = statinfo.st_dev;
        new->ino        = statinfo.st_ino;
        new->next       = pathlist;
        return new;
    }
#else

    if(pathlist_find(pathlist, pathname)) {     // only add each pathname once
        return pathlist;
    }
    else {                                      // add new pathname to head of list
        PATHLIST *new   = pathlist_new_item(pathname);
        new->next       = pathlist;
        return new;
    }
#endif
}

//  --------------------------------------------------------------------

//  DETERMINE IF A REQUIRED sha2 IS STORED IN A GIVEN LIST
static SHA2LIST *sha2list_find(SHA2LIST *sha2list, char *wanted_sha2)
{
    while(sha2list != NULL) {
	if(strcmp(sha2list->sha2, wanted_sha2) == 0) {
	    return sha2list;
	}
	sha2list	= sha2list->next;
    }
    return NULL;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
static SHA2LIST *sha2list_new_item(char *sha2)
{
    SHA2LIST *new       = calloc(1, sizeof(SHA2LIST) );
    CHECK_ALLOC(new);

    new->sha2           =  strdup(sha2);
    CHECK_ALLOC(new->sha2);
    ++nunique;

    new->next           =  NULL;        // actually, calloc() does this
    return new;
}

//  ADD A NEW sha2 TO AN EXISTING SHA2LIST
static SHA2LIST *sha2list_add(SHA2LIST *sha2list, char *pathname, char *sha2)
{
    SHA2LIST *sl        = sha2list_find(sha2list, sha2);

    if(sl) {
        sl->pathlist    = pathlist_add(sl->pathlist, pathname);
        ++sl->npaths;
        return sha2list;
    }
    else {                                      // add new sha2 to head of list
        SHA2LIST *new   = sha2list_new_item(sha2);
        new->pathlist   = pathlist_add(new->pathlist, pathname);
        ++new->npaths;
        new->next       = sha2list;
        return new;
    }
}

//  --------------------------------------------------------------------

//  FUNCTION hash_string() ACCEPTS A STRING PARAMETER,
//  AND RETURNS AN UNSIGNED 32-BIT INTEGER AS ITS RESULT
//
//  see:  https://en.cppreference.com/w/c/types/integer

static uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}

int add_pathname_to_hashtable(char *pathname, char *sha2)
{
    uint32_t h  = hash_string(sha2) % HASHTABLE_SIZE;

    hashtable[h] = sha2list_add(hashtable[h], pathname, sha2);
    return (nfiles - nunique);
}
