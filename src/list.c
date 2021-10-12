#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "list.h"

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
void list_find_dupe(LIST *list)
{   
    LIST *new_dupes = list_new();
    LIST *pCurrent = list_new();

//  ONLY ITERATE IF WE HAVE >= 2 ITEMS IN THE LIST
    while( list != NULL && list->next != NULL){
        
        pCurrent = list->next;

        // CHECKS FIRST TWO AND ADDS THEM TO LIST IFF THEY ARE DUPES
        if( (strcmp(list->file_stats->hash, pCurrent->file_stats->hash) == 0) ){
            new_dupes = list_add(new_dupes, list->file_stats);
            new_dupes = list_add(new_dupes, pCurrent->file_stats);
            ubytes += pCurrent->file_stats->bytesize;
            ++ufiles;
        }
        // WE CAN INCREMENT pCurrent HERE
        pCurrent = pCurrent->next;

        //  IFF THERE ARE MORE THAN 2 ITEMS ITERTATES THROUGH LIST TO FIND DUPES
        while(pCurrent != NULL){

            if( (strcmp(list->file_stats->hash, pCurrent->file_stats->hash) == 0) ) {

                new_dupes = list_add(new_dupes, pCurrent->file_stats);
                ubytes += pCurrent->file_stats->bytesize;
                ++ufiles;
            }
            pCurrent	= pCurrent->next;
        }
        
        list = list->next;
        pCurrent = list->next;
            
    }

    if( new_dupes != NULL ){
    // realloc dupes array
    dupes = realloc(dupes, (dupe_count + 1)*sizeof(FILES));
    CHECK_ALLOC(dupes);
    // list to dupes
    dupes[dupe_count] = new_dupes;
    //increment dupe count
    ++dupe_count;
    }
        
}


//  RETURN BYTE COUNT OF DUPES
// void list_count_dupe(LIST *list)
// {   
//     bool added_dupe = false;
//     LIST *new_dupes = list_new();

//     while(list != NULL && list->next != NULL) {
        
//         LIST *pList = list;
//         list = list->next;

//         if( list_is_dupe(list, pList) ){
//             // TODO MAKE IT MORE EFFICIENT, CURRENT TRYS TO ADD file_stats THAT HAVE ALREADY BEEN CHECKED AND ADDED
//             // BUT IT WORKS!! ie. if plist = 1, list = 2, adds both to newDupes and then if plist = 2 and list = 3 trys to add 2 again.
//             new_dupes = list_add(new_dupes, list->file_stats);
//             new_dupes = list_add(new_dupes, pList->file_stats);

//             added_dupe = true;
//             // increment ubytes and u files
//             ubytes += list->file_stats->bytesize;
//             ++ufiles;
//         }
// 	    list	= list->next;
//         pList   = pList->next;
//     }

//     if( added_dupe ){
//         // realloc dupes array
//         dupes = realloc(dupes, (dupe_count + 1)*sizeof(FILES));
//         CHECK_ALLOC(dupes);
//         // list to dupes
//         dupes[dupe_count] = new_dupes;
//         //increment dupe count
//         ++dupe_count;
//     }
// }


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

//  DETERMINE IF A REQUIRED HASH (OF A FILE) IS STORED IN A GIVEN LIST
bool list_find_hash(LIST *list, char *incoming_hash)
{   
    bool found_flag = false;
    while(list != NULL) {
        if( (strcmp(list->file_stats->hash, incoming_hash) == 0) ){
            found_hash = list_add(found_hash, list->file_stats);
            ++found_hash_count;
            found_flag = true;
        }
	    list	= list->next;
    }
    return found_flag;
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
	    printf("%s\n", list->file_stats->pathname);
	    list	= list->next;
        }
    }
}
