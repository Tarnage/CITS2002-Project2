#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

//  ON LINUX WE NEED TO PROTOTYPE THE (NON-STANDARD) strdup() FUNCTION 
//  WHY?  https://stackoverflow.com/questions/32944390/what-is-the-rationale-for-not-including-strdup-in-the-c-standard
#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

#ifndef STRCMP
#define STRCMP(p, q)   strcmp(p, q) == 0
#endif

//  ---------------------------------------------------------------------

//  'CREATE' A NEW, EMPTY LIST - JUST A NULL POINTER
LIST *list_new(void)
{
    return NULL;
}


//  DETERMINE IF A REQUIRED ITEM (A FILE) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *incoming_pathname)
{   
    while(list != NULL) 
    {
        if( STRCMP(list->file_stats->pathname, incoming_pathname) )
        {
            return true;
        }

	    list	= list->next;
    }

    return false;
}


//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(FILES *new_file)
{
    LIST *new  = malloc( sizeof(LIST) );
    CHECK_ALLOC(new);

    new->file_stats = new_file;
    CHECK_ALLOC(new->file_stats);

    new->next = NULL;
    
    return new;
}

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, FILES *new_file)
{    
    // only add each item once
    if(list_find(list, new_file->pathname)) 
    {            
        return list;
    }
    // add new item to head of list
    else 
    {                                      
        LIST *new   = list_new_item(new_file);
        new->next   = list;
        return new;
    }
}

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
void list_print(LIST *list)
{
    if(list != NULL) 
    {
        while(list != NULL) 
        {
            printf("%s\n", list->file_stats->pathname);
            list	= list->next;
        }
    }
}
