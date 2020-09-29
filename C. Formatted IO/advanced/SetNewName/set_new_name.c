/**
 * The following example uses an index table to store the positions of records in the
 * file. This approach permits direct access to a record that needs to be updated.
 */

#include <stdio.h>
#include <string.h>
#include "set_new_name.h"

extern IndexEntry_t indexTab[];  // The index table.
extern int indexLen;             // The number of table entries.

/**
 * Finds a keyword in an index table and updates the corresponding record in the file.
 * @details The file containing the records must be opened in "update mode";
 *          i.e., with the mode string "r+b".
 * @param fp A FILE pointer to the open data file
 * @param key The key
 * @param newName The new name
 * @return A pointer to the updated record, or NULL if no such record was found.
 */
Record_t *setNewName(FILE *fp, long key, const char *newName)
{
   static Record_t record;
   int i;

   for (i = 0; i < indexLen; ++i)
   {
      if (key == indexTab[i].key)  // Found the specified key.
      {
         break;
      }
   }

   if (i == indexLen)
   {
      return NULL;   // No match found.
   }

   // Set the file position to the record:
   if (fseek(fp, indexTab[i].pos, SEEK_SET) != 0)
   {
      return NULL;   // Positioning failed.
   }

   // Read the record:
   if (fread(&record, sizeof(Record_t), 1, fp) != 0)
   {
      return NULL;   // Error on reading.
   }

   if (key != record.key)  // Test the key.
   {
      return NULL;
   }
   else  // Update the record:
   {
      size_t size = sizeof(record.name);
      strncpy(record.name, newName, size - 1);
      record.name[size - 1] = '\0';

      if (fseek(fp, indexTab[i].pos, SEEK_SET) != 0)
      {
         return NULL;   // Error setting file position.
      }

      if (fwrite(&record, sizeof(Record_t), 1, fp))
      {
         return NULL;   // Error writing to file.
      }

      return &record;
   }
}
