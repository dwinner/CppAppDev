/**
 * Transaction-processing program reads a random-access file sequentially,
 * updates data already written to the file, creates new data to be placed
 * in the file, and delete data previously in the file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"

static char *const accountsFileName = "accounts.dat";

int main()
{
   FILE *cfPtr;

   if ((cfPtr = fopen(accountsFileName, "rb+")) == NULL)
   {
      printf("%s could not be opened", accountsFileName);
   }
   else
   {
      TransactionAction choiceAction;

      while ((choiceAction = enterChoice()) != EXIT)
      {
         switch (choiceAction)
         {
            case CREATE_FILE:
               textFile(cfPtr, "accounts.txt");
               break;

            case UPDATE_RECORD:
               updateRecord(cfPtr);
               break;

            case NEW_RECORD:
               newRecord(cfPtr);
               break;

            case DELETE_RECORD:
               deleteRecord(cfPtr);
               break;

            case EXIT:
               exit(EXIT_SUCCESS);
               break;

            default:
               printf("Unknow action: %d", choiceAction);
               break;
         }
      }

      fclose(cfPtr);
   }

   return EXIT_SUCCESS;
}
