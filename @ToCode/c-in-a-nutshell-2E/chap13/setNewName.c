// setNewName.c : 
// The following example uses an index table to store the positions of records in the
// file. This approach permits direct access to a record that needs to be updated.

// setNewName(): Finds a keyword in an index table
// and updates the corresponding record in the file.
// The file containing the records must be opened in
// "update mode"; i.e., with the mode string "r+b".
// Arguments: - A FILE pointer to the open data file;
//            - The key;
//            - The new name.
// Return value: A pointer to the updated record,
//               or NULL if no such record was found.
// ---------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "record.h"   // Defines the types Record_t, IndexEntry_t:
                      // typedef struct { long key; char name[32];
                      //                  /* ... */ } Record_t;
                      // typedef struct { long key, pos; } IndexEntry_t;

extern IndexEntry_t indexTab[];         // The index table.
extern int indexLen;                    // The number of table entries.

Record_t *setNewName( FILE *fp, long key, const char *newname )
{
   static Record_t record;
   int i;

   for ( i = 0; i < indexLen; ++i )
   {
      if ( key == indexTab[i].key )
         break;                             // Found the specified key.
   }
   if ( i == indexLen )
      return NULL;                          // No match found.

   // Set the file position to the record:
   if (fseek( fp, indexTab[i].pos, SEEK_SET ) != 0 )
      return NULL;                          // Positioning failed.

   // Read the record:
   if ( fread( &record, sizeof(Record_t), 1, fp ) != 1 )
      return NULL; // Error on reading.
   if ( key != record.key )                 // Test the key.
      return NULL;
   else
   {                                        // Update the record:
      size_t size = sizeof(record.name);
      strncpy( record.name, newname, size-1 );
      record.name[size-1] = '\0';

      if ( fseek( fp, indexTab[i].pos, SEEK_SET ) != 0 )
         return NULL;                       // Error setting file position.
      if ( fwrite( &record, sizeof(Record_t), 1, fp ) != 1 )
         return NULL;                       // Error writing to file.

      return &record;
   }
}
