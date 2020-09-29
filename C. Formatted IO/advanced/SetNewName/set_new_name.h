#ifndef SETNEWNAME_SET_NEW_NAME_H
#define SETNEWNAME_SET_NEW_NAME_H

#include <stdio.h>

typedef struct
{
   long key;
   char name[32];
} Record_t;

typedef struct
{
   long key,
      pos;
} IndexEntry_t;

Record_t *setNewName(FILE *fp, long key, const char *newName);

#endif //SETNEWNAME_SET_NEW_NAME_H
