//  CITS2002 Project 2 2021
//  Name(s):            Anfernee Pontilan Alviar,   Tom Nguyen
//  Student number(s):  <22886082>,                 <22914578>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

#include "duplicates.h"

// ignore_ mode  WILL IGNORE HIDDEN FILES
bool    ignore_mode         = true;

// quiet_mode  IF TRUE WILL NOT PRODUCE ANY OUTPUT TO TERMINAL.
// IT WILL SIMPLY TEST IF DIRECTORY HAS DUPLICATE FILES AND WILL EXIT_SUCCESS IF 
// NO DUPLICATE FILES ARE FOUND
bool    quiet_mode          = false;

// list_dupes IF TRUE WILL LIST ALL DUPLICATE FILES FOUND
bool    list_dupes          = false;

// list_hash IF TRUE WILL PRINT TO TERMINAL ALL FILES WITH MATCHING HASH GIVEN IN THE COMMAND-LINE
bool    list_hash           = false;
char    *input_hash;                    // stores the hash given from command-line
LIST    *found_hash         = NULL;     // stores all files matched by inputhash
 
// find_file_mode IF TRUE WILL PRINT ALL FILES THAT MATCH THE HASH OF THE FILENAME GIVEN IN COMMAND-LINE
bool    find_file_mode      = false;
char    *wanted_file;                   // stores the filename 
char    *wanted_file_hash   = "\0";     // when file is found it stores the hash of the filename
char    *wanted_pathname;               // stores the path of the wanted file
bool    w_file_found        = false;    // have we found the file
// 
int     dupe_count;                     // used to dynamically allocate **dupes
LIST    **duplicates        = NULL;     // list of all duplicates found
int     found_hash_count;               // count of all duplicate files found
FILES   *files;                         // array of all found files

// INITILIZE COUNTERS TO ZERO
int     file_count      = 0;
int     files_w_dupes   = 0;
int     nfiles          = 0;
int     nbytes          = 0;
int     ufiles          = 0;
int     ubytes          = 0;

void usage(char *progname) 
{
   printf ("Usage: %s [OPTION]... [FILE]...\n", progname);

      fputs (("\
Locate and report duplicate files in, and below, any number of named directory.\n\
\n\
"), stdout);

      fputs (("\
  -a,       do not ignore entries starting with .\n\
\n\
  -A,       advanced mode. Only Advanced task 1. implemented.\n\
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
  -m,       Not implemented.\n\
\n\
  -q,       duplicates executes quietly, simply testing if the named directory contains any duplicate files.\n\
            duplicates -q produces no output at all, simply terminating with EXIT_SUCCESS if there are no duplicates\n\
            (i.e. storage is already minimized), or with EXIT_FAILURE otherwise.\n\
\n\
"), stdout);

   exit(EXIT_FAILURE);
}

// ITERATES THROUGH THE HASHTABLE TO FIND DUPLICATES
// CALLS find_duplicates FUNCTION TO FIND DUPLICATES OF A SPECIFIC FILE WHILE ITERATING
void count_duplicates(HASHTABLE *hashtable)
{   
    for(int i = 0; i < HASHTABLE_SIZE; ++i)
    {
        find_duplicates(hashtable[i]);
    }
}

//  DETERMINE IF A REQUIRED ITEM (A FILE) IS A DUPLICATE
//  ITERATES THROUGH A HASHTABLE ENTRY (LIST) TO FIND DUPLICATES FOR THE FILE INSIDE THE HASHTABLE ELEMENT
void find_duplicates(LIST *list)
{   
    LIST *new_dupes = list_new();
    LIST *pCurrent = list_new();

//  ONLY ITERATE IF WE HAVE >= 2 ITEMS IN THE LIST
    while( list != NULL && list->next != NULL )
    {
        pCurrent = list->next;

        // CHECKS FIRST TWO AND ADDS THEM TO LIST IFF THEY ARE DUPES
        if( STRCMP(list->file_stats->hash, pCurrent->file_stats->hash) )
        {
            new_dupes = list_add(new_dupes, list->file_stats);
            new_dupes = list_add(new_dupes, pCurrent->file_stats);
            ubytes += pCurrent->file_stats->bytesize;
            ++files_w_dupes;
        }
        // WE CAN INCREMENT pCurrent HERE
        pCurrent = pCurrent->next;

        //  IFF THERE ARE MORE THAN 2 ITEMS ITERTATES THROUGH LIST TO FIND DUPES
        while(pCurrent != NULL)
        {
            if( STRCMP(list->file_stats->hash, pCurrent->file_stats->hash) ) 
            {
                new_dupes = list_add(new_dupes, pCurrent->file_stats);
            }
            
            pCurrent = pCurrent->next;
        }
        
        list = list->next;
        pCurrent = list->next;
            
    }

    // IF A DUPLICATE LIST WAS MADE IN THE PREVIOUS LOOP
    if( new_dupes != NULL )
    {
        // realloc dupes array
        duplicates = realloc(duplicates, (dupe_count + 1)*sizeof(FILES));
        CHECK_ALLOC(duplicates);
        // list to dupes
        duplicates[dupe_count] = new_dupes;
        //increment dupe count
        ++dupe_count;
    }
}


//  DETERMINE IF A REQUIRED HASH (OF A FILE) IS STORED IN A GIVEN LIST
bool list_find_hash(LIST *list, char *incoming_hash)
{   
    bool found_flag = false;
    while(list != NULL) 
    {
        if( STRCMP(list->file_stats->hash, incoming_hash) )
        {
            found_hash = list_add(found_hash, list->file_stats);
            ++found_hash_count;
            found_flag = true;
        }
	    
        list = list->next;
    }
    return found_flag;
}


//  PRINT EACH DUPE (THE RELATIVE PATHNAME) IN A GIVEN LIST TO stdout
void print_dupes(LIST *list)
{
    if(list != NULL) 
    {
        while(list != NULL) 
        {
            char *pName = list->file_stats->pathname;
	        printf("%s\t", pName );
	        list	= list->next;
        }
        printf("\n");
    }
}

//TODO CHECK IF FILE IS THE SAME
void print_matching_files(HASHTABLE *incoming_table)
{   
    if(!STRCMP(wanted_file_hash, "\0"))
    {
        int32_t h = hash_string(wanted_file_hash) % HASHTABLE_SIZE;
        LIST *location = incoming_table[h];
        int count = 0;
        while(location != NULL)
        {
            if( (STRCMP(location->file_stats->hash, wanted_file_hash)) 
                && (!STRCMP(wanted_pathname, location->file_stats->pathname)) )
            {   
                char *pName = location->file_stats->pathname;
                printf("%s\n", pName );
                ++count;
            }
            location = location->next;
        }
        if(count > 0)
        {
            exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_FAILURE);
}


void print_matching_hash(HASHTABLE *incoming_table)
{
    if( hashtable_find_hash(incoming_table, input_hash) ) 
    {
        list_print(found_hash);
        exit(EXIT_SUCCESS);
    }
    else exit(EXIT_FAILURE);
    
}


void quiet_mode_summary()
{   
    // IF nbytes DOES NOT EQUAL ubytes WE HAVE DUPLICATES
    // TODO COULD DO A "PROPER" CHECK FOR DUPES SINCE WE ALREADY COUNT DUPES
    if(nbytes != ubytes)
    {
        printf("DUPLICATE FILES FOUND\n");
        exit(EXIT_FAILURE);
    }
    printf("SUCCESS\n");
    exit(EXIT_SUCCESS);
}


void print_dir_summary()
{
    printf("%i\n", file_count);
    printf("%i\n", nbytes);
    printf("%i\n", ufiles);
    printf("%i\n", ubytes);
}


int main(int argc, char *argv[])
{
//  ENSURE THAT PROGRAM HAS CORRECT NUMBER OF ARGUMENTS
    if (argc < 2) 
    {
        usage(argv[0]);
    }
    else 
    {
        int		opt;
        //  PROCESS COMMAND-LINE OPTIONS
        opterr	= 0;
        while((opt = getopt(argc, argv, OPTLIST)) != -1) 
        {
            switch (opt) 
            {
                case 'a':
                    ignore_mode = false;
                    break;
                case 'A':
                    exit(EXIT_SUCCESS);
                    break;
                case 'f':
                    // CHECK IF A FILENAME WAS PROVIDED
                    if(argc < 4)
                    {
                        usage(argv[0]);
                    }
                    find_file_mode = true;
                    wanted_file = optarg;
                    break;
                case 'h':
                    // CHECK IF A HASH WAS PROVIDED
                    if(argc < 4)
                    {
                        usage(argv[0]);
                    }
                    list_hash = true;
                    input_hash = optarg;
                    break;
                case 'l':
                    list_dupes = true;
                    break;
                case 'm':
                    exit(EXIT_FAILURE);         // not implemented
                case 'q':
                    quiet_mode = true;
                    break;
                default: /* '?' */
                    usage(argv[0]);
                    exit(EXIT_FAILURE);
            }
        }

    //  INITIALIZE HASHTABLE FOR CHECKING DUPLICATES
        HASHTABLE  *hash_table = hashtable_new();

        // LOOP THROUGH DIRECTORY ARGUMENTS IN THE COMMAND-LINE
        for(int i = optind; i < argc; ++i)
        {
            //  START THE SEARCH FOR ALL FILES
            scan_dir_recur(argv[i]);

            //  ADD ALL FILES TO hash_table TO CHECK FOR DUPLICATES
            for(int i = 0; i < nfiles; ++i)
            {   
                // IF NOT FOUND, ADD TO HASHTABLE
                if(!hashtable_find(hash_table, files->pathname)) 
                {
                    hashtable_add(hash_table, files);
                    ++file_count;
                }

                ++files;                        // increment pointer
            }

            // SET POINTER TO NULL TO REALLOCATE NEW MEMORY FOR NEXT DIRECTORY (IF IN CMD-LINE)
            files = NULL;                       // reset pointer

            nfiles = 0;                         // reset nfiles
        }
        
        //  CALCULATE THE DUPLICATES UNIQUE FILES AND UNIQUE BYTES
        count_duplicates(hash_table);
        ufiles = file_count - files_w_dupes;
        ubytes = nbytes - ubytes;

        // CHECK WHAT OPTIONS ARE MET (IF NOT CONTRADICTORY)
        
        // FIND THE FILE MATCHING THE INPUT FILE FROM THE COMMAND-LINE
        if( find_file_mode )
        {
            // ITERATE THROUGH HASH TABLE, FIND FILE MATCHING WITH ARGUMENT AFTER -f
            print_matching_files(hash_table);
        }
        // FIND THE HASH MATCHING THE INPUT HASH FROM THE COMMAND-LINE
        else if( list_hash )
        {
            print_matching_hash(hash_table);
        }
        // LIST FOUND DUPLICATES   
        else if( list_dupes )
        {
            for(int i = 0; i < dupe_count; ++i)
            {
                print_dupes(duplicates[i]);
            }
            exit(EXIT_SUCCESS);
        }
        // DO NOT PRINT ufiles, nfiles, etc.
        // EXIT_SUCCESS IF NO DUPLICATES FOUND
        // EXIT_FAILURE OTHERWISE 
        else if( quiet_mode )
        {
            quiet_mode_summary();
        }
        // PRINT SUMMARY 
        else 
        {
            print_dir_summary();
        }
    }

    return 0;
}
