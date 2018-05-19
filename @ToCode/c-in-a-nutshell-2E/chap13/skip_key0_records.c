// skip_key0_records.c : 
// The following example assumes that records have been saved in the
// file records.dat. 
// A key value of 0 indicates that arecord has been marked as deleted.
// In copying records the program skips over records whose key is 0.

// Copy records to a new file, filtering out those with the key 0.
// ---------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN 100       // Maximum number of records in the buffer.
// A structure type for the records:
typedef struct { long key;
                 char name[32];
                 /* ... other fields in the record ... */ } Record_t;

char inFile[ ] = "records.dat",                      // Filenames.
     outFile[ ] = "packed.dat";

// Terminate the program with an error message:
static inline void error_exit( int status, const char *error_msg )
{
   fputs( error_msg, stderr );
   exit( status );
}

int main()
{
   FILE *fpIn, *fpOut;
   Record_t record, *pArray;
   unsigned int i;

   if (( fpIn = fopen( inFile, "rb" )) == NULL )         // Open to read.
      error_exit( 1, "Error on opening input file." );

   else if (( fpOut = fopen( outFile, "wb" )) == NULL )  // Open to write.
      error_exit( 2, "Error on opening output file." );

   else                                                  // Create the buffer.
      if ( (pArray = malloc( ARRAY_LEN * sizeof(Record_t) )) == NULL )
         error_exit( 3, "Insufficient memory." );

   i = 0;                                       // Read one record at a time:
   while ( fread( &record, sizeof(Record_t), 1, fpIn ) == 1 )
   {
      if ( record.key != 0L )                   // If not marked as deleted ...
      {                                         // ... then copy the record:
         pArray[i++] = record;
         if ( i == ARRAY_LEN )             // Buffer full?
         {                                 // Yes: write to file.
            if ( fwrite( pArray, sizeof(Record_t), i, fpOut) < i )
               break;
            i = 0;
         }
      }
   }
   if ( i > 0 && !ferror(fpOut) )          // Write the remaining records.
      fwrite( pArray, sizeof(Record_t), i, fpOut );

   if ( ferror(fpOut) )                                  // Handle errors.
      error_exit( 4, "Error on writing to output file." );
   else if ( ferror(fpIn) )
      error_exit( 5, "Error on reading input file." );

   return 0;
}
