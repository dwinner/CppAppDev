#ifndef SETNEWNAME_SET_NEW_NAME_H
#define SETNEWNAME_SET_NEW_NAME_H

#include <stdio.h>

/**
 * Record
 */
struct Record
{
   long key;
   char name[32];
};

/**
 * Record_t
 */
typedef struct Record Record_t;

/**
 * IndexEntry
 */
struct IndexEntry
{
   long key,
      pos;
};

/**
 * IndexEntry
 */
typedef struct IndexEntry IndexEntry_t;

Record_t *setNewName(FILE *fp, long key, const char *newName);

#endif //SETNEWNAME_SET_NEW_NAME_H
