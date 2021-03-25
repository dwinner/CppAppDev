/**
 * Writing data randomly to a random-access file
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Client data
 */
struct clientData
{
   unsigned int accountNumber;   // account number
   char lastName[15];   // account last name
   char firstName[10];  // account first name
   double balance;   // account balance
};

int main()
{
   FILE *cfPtr;

   if ((cfPtr = fopen("accounts.dat", "rb+")) == NULL)
   {
      puts("File could not be opened");
   }
   else
   {
      struct clientData client = {0, "", "", 0.0};

      printf("%s", "Enter account number (1 to 100, 0 to end input: )");
      scanf("%d", &client.accountNumber);

      while (client.accountNumber != 0)
      {
         printf("%s", "Enter lastname, firstname, balance: ");

         fscanf(stdin, "%14s%9s%lf",
                client.lastName, client.firstName, &client.balance);

         // seek position in file to user-specified record
         fseek(cfPtr, (client.accountNumber - 1) * sizeof(struct clientData), SEEK_SET);

         // write user-specified information in file
         fwrite(&client, sizeof(struct clientData), 1, cfPtr);

         printf("%s", "Enter account number: ");
         scanf("%d", &client.accountNumber);
      }

      fclose(cfPtr);
   }

   return EXIT_SUCCESS;
}