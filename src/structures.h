//DECLARE STRUCTURES
#ifndef STRUCTURES_H
#define STRUCTURES_H
// -----------------------------------------------------------------------------------------------
// DEFINED TYPEDEFS

// DATA TYPE FOR READING IN FILES
typedef struct _files {
    char           *pathname;
    char           *filename;
    char           *hash;
    int             bytesize;
} FILES;

typedef struct _list {
     FILES          *file_stats;
     struct _list   *next;
} LIST;

#endif
