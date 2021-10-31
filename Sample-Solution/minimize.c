#include "duplicates.h"
#include "hashtable.h"

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

#if     defined(ADVANCED)
int minimize_duplicates(void)
{
    int nfound  = 0;

//  DO WE HAVE ANY FILES STORED?
    if(hashtable) {
        for(int h=0 ; h<HASHTABLE_SIZE ; ++h) {
            SHA2LIST    *sl = hashtable[h];

            while(sl != NULL) {
                PATHLIST *pl0   = sl->pathlist;

//  IFF WE HAVE AT LEAST TWO DUPLICATE FILES (WITH THIS sha2 VALUE)
                if(pl0 && pl0->next) {
                    PATHLIST *pl1  = pl0->next;

                    ++nfound;
                    while(pl1 != NULL) {
//  ONLY UNLINK AND LINK FILES THAT ARE NOT ALREADY LINKED
                        if(! same_file(pl0, pl1) ) {
                            if(unlink(pl1->pathname) != 0) {
                                perror(pl1->pathname);
                            }
                            else {
                                if(link(pl0->pathname, pl1->pathname) != 0) {
                                    perror(pl0->pathname);
                                }
                                else {
//  PATCH OUR HASHTABLE
//  NEWLY LINKED FILES NOW HAVE SAME DEVICE AND INODE NUMBERS
                                    pl1->dev    = pl0->dev;
                                    pl1->ino    = pl0->ino;

//  printf("unlink(\"%s\");\tlink(\"%s\", \"%s\");\n",
//          pl1->pathname, pl0->pathname, pl1->pathname);
                                }
                            }
                        }
                        pl1  = pl1->next;
                    }
                }
                sl  = sl->next;
            }
        }
    }
    return nfound;
}
#endif
