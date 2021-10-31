#include "duplicates.h"
#include "hashtable.h"

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

//  LISTS ALL DUPLICATE FILES FOUND.
//  EACH OUTPUT LINE CONSISTS OF THE PATHNAMES OF TWO OR MORE DUPLICATE FILES
//  THE PATHNAMES OF DUPLICATE FILES ARE SEPARATED BY THE tab CHARACTER.
int list_duplicates(void)
{
    int nduplicates  = 0;

//  DO WE HAVE ANY FILES STORED?
    if(hashtable) {
        for(int h=0 ; h<HASHTABLE_SIZE ; ++h) {
            SHA2LIST    *sl = hashtable[h];

            while(sl != NULL) {
                PATHLIST    *pl = sl->pathlist;

//  IFF WE HAVE AT LEAST TWO DUPLICATE FILES (WITH THIS sha2 VALUE)
                if(pl && pl->next) {
                    while(pl != NULL) {
                        ++nduplicates;
                        fputs(pl->pathname, stdout);
                        pl  = pl->next;
                        if(pl) {                // any more to come?
                            fputs("\t", stdout);
                        }
                    }
                    fputs("\n", stdout);
                }
                sl  = sl->next;
            }
        }
    }
    return nduplicates;
}

#if defined(ADVANCED)
static int count_hard_linked_paths(SHA2LIST *sl)
{
    PATHLIST    *pl = sl->pathlist;
    PATHLIST    *all[sl->npaths];
    int         n_diff_links  = 0;

    while(pl != NULL) {
        int n=0;

        while(n < n_diff_links) {
            if(same_file(pl, all[n])) {
                break;
            }
            ++n;
        }
        if(n == n_diff_links) {
            all[n_diff_links++]    = pl;
        }
        pl          = pl->next;
    }
    return n_diff_links;
}
#endif

//  REPORT REQUIRED STATISTICS, ONE PER LINE
void list_statistics(void)
{
    int     nfiles      = 0;
    size_t  totalsize   = 0;
    int     nunique     = 0;
    size_t  minsize     = 0;

//  DO WE HAVE ANY FILES STORED?
    if(hashtable) {
        for(int h=0 ; h<HASHTABLE_SIZE ; ++h) {
            SHA2LIST *sl    = hashtable[h];

            while(sl != NULL) {
                ++nunique;

                struct stat statinfo;
                size_t      eachsize    = 0;        // as all have same size

                if(stat(sl->pathlist->pathname, &statinfo) == 0) {
                    eachsize    = statinfo.st_size;
                    minsize     += eachsize;
                }

#if defined(ADVANCED)
                nfiles      += sl->npaths;
                totalsize   += count_hard_linked_paths(sl) * eachsize;
#else
                PATHLIST *pl    = sl->pathlist;

                while(pl != NULL) {
                    ++nfiles;
                    totalsize   += eachsize;
                    pl          = pl->next;
                }
#endif
                sl  = sl->next;
            }
        }
    }

//  LIST REQUIRED STATISTICS, ONE PER LINE
    printf("%i\t- total files\n",  nfiles);
    printf("%zu\t- total bytes\n", totalsize);
    printf("%i\t- unique files\n",  nunique);
    printf("%zu\t- possible minimum bytes\n", minsize);
}
