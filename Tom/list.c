#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "duplicates.h"

//  ON LINUX WE NEED TO PROTOTYPE THE (NON-STANDARD) strdup() FUNCTION 
//  WHY?  https://stackoverflow.com/questions/32944390/what-is-the-rationale-for-not-including-strdup-in-the-c-standard
#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

//  ---------------------------------------------------------------------

//  'CREATE' A NEW, EMPTY LIST - JUST A NULL POINTER
LIST *list_new(void)
{
    return NULL;
}

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *name, char *hash, int size)
{   
    while(list != NULL) {
        if( (strcmp(list->fname, name) == 0) && (strcmp(list->fhash, hash) == 0) ){
            return true;
        }
	    list	= list->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
// TODO add size
LIST *list_new_item(char *newfname, char *newfhash, int newfsize)
{
    LIST *new       = malloc( sizeof(LIST) );
    CHECK_ALLOC(new);
    new->fname     =  strdup(newfname);
    new->fhash     =  strdup(newfhash);
    new->fsize     =  newfsize;
    CHECK_ALLOC(new->fname);
    CHECK_ALLOC(new->fhash);
    //TODO add checks for hash and size
    new->next       =  NULL;
    return new;
}

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *newfname, char * newfhash, int newfsize)
{    
    //TODO add more checks for dupes
    if(list_find(list, newfname, newfhash, newfsize)) {            // only add each item once
        return list;
    }
    else {                                      // add new item to head of list
        LIST *new   = list_new_item(newfname, newfhash, newfsize);
        new->next   = list;
        return new;
    }
}

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
void list_print(LIST *list)
{
    if(list != NULL) {
        while(list != NULL) {
	    printf("%s-%i-%s", list->fname, list->fsize, list->fhash);
	    if(list->next != NULL) {
	        printf(" -> ");
            }
	    list	= list->next;
        }
	printf("\n");
    }
}
