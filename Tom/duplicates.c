#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

#include "duplicates.h"
#include "list.h"
#include "hashtable.h"

//
bool    ignore_mode         = true;
bool    quiet_mode          = false;
bool    list_dupes          = false;
bool    list_hash           = false;
bool    find_file_mode      = false;
int     pathname_len;
char    *iwd;

char    *hash;
char    *find_me;
char    *find_me_hash;
LIST    **dupes             = NULL;
int     dupe_count; // used to dynamically allocate **dupes
int     found_hash_count; // defned in duplicates.c and incremented in list.c
LIST    *found_hash         = NULL;
char    *find_me_file;
FILES   *files;   // array of found files

void usage(char *progname) {
   //fprintf(stderr, USAGE_FMT, progname);
   printf ("Usage: %s [OPTION]... [FILE]...\n", progname);

      fputs (("\
Locate and report duplicate files in, and below, a named directory.\n\
\n\
"), stdout);

      fputs (("\
  -a,       do not ignore entries starting with .\n\
\n\
  -A,       advanced mode\n\
\n\
  -f,       find and list, one per line, the relative pathnames of all files whose SHA2\n\
            hash matches that of the indicated file. The name of the indicated file is not listed.\n\
            duplicates -f terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise\n\
\n\
  -h,       find and list, one per line, the relative pathnames of all files with the indicated SHA2 hash.\n\
            duplicates -h terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise.\n\
\n\
  -l,       duplicates lists all duplicate files found. Each line of output consists of the relative pathnames of two or more files\n\
            that are duplicates of each other. The pathnames of duplicate files (on the same line line) must be separated by the TAB character.\n\
\n\
  -m,       duplicates minimizes the total number of bytes required to store all files' data by modifying the directory structure being considered.\n\
\n\
  -q,       duplicates executes quietly, simply testing if the named directory contains any duplicate files.\n\
            duplicates -q produces no output at all, simply terminating with EXIT_SUCCESS if there are no duplicates\n\
            (i.e. storage is already minimized), or with EXIT_FAILURE otherwise.\n\
\n\
"), stdout);

   exit(EXIT_FAILURE);
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
        if( STRCMP(list->file_stats->hash, pCurrent->file_stats->hash) ){
            new_dupes = list_add(new_dupes, list->file_stats);
            new_dupes = list_add(new_dupes, pCurrent->file_stats);
            ubytes += pCurrent->file_stats->bytesize;
            ++ufiles;
        }
        // WE CAN INCREMENT pCurrent HERE
        pCurrent = pCurrent->next;

        //  IFF THERE ARE MORE THAN 2 ITEMS ITERTATES THROUGH LIST TO FIND DUPES
        while(pCurrent != NULL){

            if( STRCMP(list->file_stats->hash, pCurrent->file_stats->hash) ) {

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


//  DETERMINE IF A REQUIRED HASH (OF A FILE) IS STORED IN A GIVEN LIST
bool list_find_hash(LIST *list, char *incoming_hash)
{   
    bool found_flag = false;
    while(list != NULL) {
        if( STRCMP(list->file_stats->hash, incoming_hash) ){
            found_hash = list_add(found_hash, list->file_stats);
            ++found_hash_count;
            found_flag = true;
        }
	    list	= list->next;
    }
    return found_flag;
}


//  PRINT EACH DUPE (THE RELATIVE PATHNAME) IN A GIVEN LIST TO stdout
void print_dupes(LIST *list)
{
    if(list != NULL) {
        while(list != NULL) {
            char *pName = list->file_stats->pathname + pathname_len;
	        printf("%s\t", pName );
	        list	= list->next;
        }
        printf("\n");
    }
}

//TODO CHECK IF FILE IS THE SAME
void print_matching_files(HASHTABLE *incoming_table)
{   
    int32_t h	= hash_string(find_me_hash) % HASHTABLE_SIZE;

    LIST *location = incoming_table[h];
    while(location != NULL){
        if( (STRCMP(location->file_stats->hash, find_me_hash)) &&
                (!STRCMP(find_me_pathname, location->file_stats->pathname)) ){
            char *pName = location->file_stats->pathname + pathname_len;
	        printf("%s\n", pName );
        }
        location	= location->next;
    }

}


void print_matching_hash(HASHTABLE *incoming_table)
{
    if( hashtable_find_hash(incoming_table, hash) ) {
        list_print(found_hash);
        exit(EXIT_SUCCESS);
    }
    else{
        exit(EXIT_FAILURE);
    }
}


void quiet_mode_summary()
{   
    // IF nbytes DOES NOT EQUAL ubytes WE HAVE DUPLICATES
    // TODO COULD DO A "PROPER" CHECK FOR DUPES SINCE WE ALREADY COUNT DUPES
    if(nbytes != ubytes){
        printf("DUPLICATE FILES FOUND\n");
        exit(EXIT_FAILURE);
    }
    printf("SUCCESS\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc < 2) {
        usage(argv[0]);
    }
    else {

    int		opt;

//  PROCESS COMMAND-LINE OPTIONS
    opterr	= 0;
    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {
            case 'a':
                printf("Option [-a] was selected\n");
                ignore_mode = false;
                break;
            case 'A':
                printf("Option [-A] was selected\n");
                break;
            case 'f':
                printf("Option [-f] was selected\n");
                find_file_mode = true;
                find_me = optarg;
                break;
            case 'h':
                printf("Option [-h] was selected\n");
                list_hash = true;
                hash = optarg;
                break;
            case 'l':
                printf("Option [-l] was selected\n");
                list_dupes = true;
                break;
            case 'm':
                printf("Option [-m] was selected\n");
                break;
            case 'q':
                printf("Option [-q] was selected\n");
                quiet_mode = true;
                break;
            default: /* '?' */
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
//  SAVE INCOMING WORKING DIR
    iwd = argv[optind];
// SAVE THE SIZE OF THE PATHNAME TO GET THE RELATIVE PATHNAME OF A FILE
    pathname_len = strlen(iwd);


//  INITIALIZE HASHTABLE FOR CHECKING DUPLICATES
    HASHTABLE   *hash_table = hashtable_new();

    scan_dir_recur(iwd);
    //scan_dir_recur("../tests");
    //scan_dir_recur("..");
    //scan_dir_recur("/mnt/d/Github/CITS2002-Project2/tests");
    //scan_dir_recur("/mnt/d/Github/CITS2002-Project2/Tom");

//  ADD ALL FILES TO hash_table TO CHECK FOR DUPLICATES
    FILES *ptemp = files;               // store start of files;
    for(int i = 0; i < nfiles; ++i){
       hashtable_add(hash_table, files);
       ++files;
    }
    files = ptemp;                      // return files back to start

    //hashtable_print(hash_table);
    hashtable_count_dupes(hash_table);
    
    ufiles = nfiles - ufiles;
    ubytes = nbytes - ubytes;

// PRINTS DUPE IF OPT -l IS SELECTED
    if( list_dupes ){
        for(int i = 0; i < dupe_count; ++i){
            print_dupes(dupes[i]);
        }
    }

    //printf("%s\n", strSHA2("../tests/for_testing_hash.txt"));



//  PRINT SUMMARY IFF quiet_mode = false
//  TODO THINK ABOUT CONTROL FLOW
//  IF quiet_mode == true THIS WILL EXIT PROGRAM AND NOTHING
//  BELOW WILL EXECUTE. ie. THINK ABOUT - IF WE WANT MULTIPLE OPTIONS TO EXECUTE 
    if( quiet_mode ){
        quiet_mode_summary();
    }
    else if( list_hash ){
        print_matching_hash(hash_table);
    }
    else if( find_file_mode ){
        print_matching_files(hash_table);
    }
    else{
        print_dir_summary();
    }
// //  TERMINATE PROGRAM, INDICATING SUCCESS
         exit(EXIT_SUCCESS);
     }
    return 0;
}
