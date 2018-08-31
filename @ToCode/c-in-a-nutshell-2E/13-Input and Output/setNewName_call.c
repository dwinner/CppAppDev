// setNewName_call.c : 
// The main function creates an index table for the file records.dat
// and calls the setNewName() function.

#include <stdio.h>
#include <string.h>
#include "record.h"   // Defines the types Record_t, IndexEntry_t:
                      // typedef struct { long key; char name[32];
                      //                  /* ... */ } Record_t;
                      // typedef struct { long key, pos; } IndexEntry_t;

#define TAB_LEN 100
IndexEntry_t indexTab[TAB_LEN];         // The index table.
int indexLen = 0;                       // The number of table entries.

char dataFile[] = "records.dat";

int main()
{
    FILE *fpData = NULL;
    Record_t record;
    int i;

    if( (fpData = fopen( dataFile, "r+b")) == NULL)
    {
        fprintf( stderr, "Error on opening the file \"%s\".\n", dataFile);
        return 1;
    }
    for( i = 0; i < TAB_LEN; ++i)
    {
        indexTab[i].pos = ftell(fpData);          // current file position.
        if( fread( &record, sizeof(Record_t), 1, fpData) < 1)
            break;
        indexTab[i].key = record.key;
//        printf("%4ld : %ld\n", indexTab[i].key, indexTab[i].pos);
    }
    if( !feof( fpData))
    {
        fprintf( stderr, "Error on reading the file \"%s\".\n", dataFile);
        return 2;
    }
    indexLen = i;

    if( setNewName( fpData, 1825L, "John Quincy") == NULL)
       fprintf( stderr, "Error on updating the file \"%s\".\n", dataFile);

    // List the records:
    rewind( fpData);
    while( fread( &record, sizeof(Record_t), 1, fpData) == 1) 
    {
       printf("%8ld : %s\n", record.key, record.name);
    }

    fclose( fpData);
    return 0;
}
