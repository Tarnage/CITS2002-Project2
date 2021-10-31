
//  RESEARCH SHOWS THAT USING PRIME-NUMBERS CAN IMPROVE PERFORMANCE
//  c.f.  https://www.quora.com/Why-should-the-size-of-a-hash-table-be-a-prime-number
#define	HASHTABLE_SIZE		997


//  ALL pathnames ON EACH PATHLIST HAVE THE SAME VALUE OF SHA2(pathname)
typedef struct _pathlist {
    char                *pathname;
#if	defined(ADVANCED)
    dev_t		dev;		// device inode resides on
    ino_t		ino;		// inode's number
#endif
    struct _pathlist    *next;
} PATHLIST;

#if defined(ADVANCED)
#define same_file(fl0, fl1)     (fl0->dev == fl1->dev && fl0->ino == fl1->ino)

#else   // BASIC
#define same_file(fl0, fl1)     (strcmp(fl0->pathname, fl1->pathname) == 0)
#endif


//  ALL ENTRIES ON EACH SHA2LIST HAVE THE SAME VALUE OF hash_string(sha2)
typedef struct _sha2list {
    char                *sha2;
    PATHLIST            *pathlist;
    int                 npaths;         // number of paths with this sha2
    struct _sha2list    *next;
} SHA2LIST;

typedef     SHA2LIST    HASHTABLE;

//  DEFINED IN hashtable.c
extern  int add_pathname_to_hashtable(char *pathname, char *sha2);

extern HASHTABLE        **hashtable;

