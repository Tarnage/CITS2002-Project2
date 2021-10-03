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

//  DETERMINE IF A REQUIRED ITEM (A FILE) IS A DUPELICATE
bool list_find_dupe(LIST *list, FILES *incoming_file)
{   
    while(list != NULL) {
        if( (strcmp(list->file_stats->hash, incoming_file->hash) == 0) ){
            return true;
        }
	    list	= list->next;
    }
    return false;
}


//  DETERMINE IF A REQUIRED ITEM (A FILE) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *incoming_pathname)
{   
    while(list != NULL) {
        if( (strcmp(list->file_stats->pathname, incoming_pathname) == 0) ){
            return true;
        }
	    list	= list->next;
    }
    return false;
}


//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(FILES *new_file)
{
    LIST *new       = malloc( sizeof(LIST) );
    CHECK_ALLOC(new);
    new->file_stats = new_file;
    CHECK_ALLOC(new->file_stats);
    new->next       =  NULL;
    return new;
}

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, FILES *new_file)
{    
    if(list_find(list, new_file->pathname)) {            // only add each item once
        return list;
    }
    else {                                      // add new item to head of list
        LIST *new   = list_new_item(new_file);
        new->next   = list;
        return new;
    }
}

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
void list_print(LIST *list)
{
    if(list != NULL) {
        while(list != NULL) {
	    printf("(%s-%i-%s)", list->file_stats->pathname, list->file_stats->bytesize, list->file_stats->hash);
	    if(list->next != NULL) {
	        printf(" -> ");
            }
	    list	= list->next;
        }
	printf("\n");
    }
}
