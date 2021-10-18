//DECLARE STRUCTURES
#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <time.h>
// -----------------------------------------------------------------------------------------------
// DEFINED TYPEDEFS

// DATA TYPE FOR READING IN FILES
typedef struct _files {
    char           *pathname;
    char           *filename;
    char           *hash;
    int             bytesize;
    time_t          mtime;
} FILES;

typedef struct _list {
     FILES          *file_stats;
     struct _list   *next;
} LIST;

#endif
