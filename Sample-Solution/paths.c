#include "duplicates.h"
#include "hashtable.h"

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

int add_pathname(char *pathname)
{
//  IF OUR FIRST ADDITION, ALLOCATE SPACE FOR A NEW HASHTABLE
    if(hashtable == NULL) {
        hashtable  = calloc(HASHTABLE_SIZE, sizeof(hashtable[0]));
        CHECK_ALLOC(hashtable);
    }

    char *sha2  = strSHA2(pathname);

//  ONLY ADD THIS PATHNAME IF WE CAN CALCULATE THE SHA2 OF ITS CONTENTS
    if(sha2 != NULL) {
        return add_pathname_to_hashtable(pathname, sha2);
    }
    return 0;
}
