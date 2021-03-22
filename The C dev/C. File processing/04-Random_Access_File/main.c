/**
 * Creating a random-access file sequentially
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   unsigned int accountNumber;   // account number
   char lastName[15];   // account last name
   char firstName[10];  // account first name
   double balance;   // account balance
} ClientData;

int main()
{
   FILE *cfPtr;

   if ((cfPtr = fopen("accounts.dat", "wb")) == NULL)
   {
      puts("File could not be opened.");
   }
   else
   {
      ClientData blankClient = {0, "", "", 0.0};

      for (size_t i = 1; i <= 100; ++i)
      {
         fwrite(&blankClient, sizeof(ClientData), 1, cfPtr);
      }

      fclose(cfPtr);
   }
   return EXIT_SUCCESS;
}
