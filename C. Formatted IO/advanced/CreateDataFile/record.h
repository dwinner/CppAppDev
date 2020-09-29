#ifndef CREATEDATAFILE_RECORD_H
#define CREATEDATAFILE_RECORD_H

typedef struct
{
   long key;
   char name[32];
} Record_t;

typedef struct
{
   long key, pos;
} IndexEntry_t;

#endif //CREATEDATAFILE_RECORD_H
