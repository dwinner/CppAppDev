/**
 * Reading a random-access file sequentially
 */

#include <stdio.h>
#include <stdlib.h>

struct clientData
{
   unsigned int accountNumber;
   char lastName[15];
   char firstName[10];
   double balance;
};

typedef FILE File;

int main()
{
   File *cfPtr;

   if ((cfPtr = fopen("accounts.dat", "rb")) == NULL)
   {
      puts("File could not be opened");
   }
   else
   {
      printf("%-8s%-16s%-11s%10s\n",
             "Account", "Last name", "First name", "Balance");

      // read all records from file (until eof)
      while (!feof(cfPtr))
      {
         struct clientData client = {0, "", "", 0.0};
         int result = fread(&client, sizeof(struct clientData), 1, cfPtr);
         if (result != 0 && client.accountNumber != 0)
         {
            printf("%-8d%-16s%-11s%10.2f\n",
                   client.accountNumber, client.lastName, client.firstName, client.balance);
         }
      }

      fclose(cfPtr);
   }

   return EXIT_SUCCESS;
}