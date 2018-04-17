/**
 * Transaction C-style interface implementation
 */

#include "transaction.h"

/**
 * Print client information
 * @param ptrClient Client
 */
static void printClient(const ClientData *ptrClient);

/**
 * Get blank client
 * @return Blank client
 */
static ClientData getBlankClient();

/**
 * Reset account position
 * @param fPtr File pointer
 * @param accountNumber Account number
 */
static void resetAccountPosition(FILE *fPtr, unsigned int accountNumber);

TransactionAction enterChoice(void)
{
   // display available options
   printf("%s", "\nEnter your choice\n"
      "1 - store a formatted text file of accounts called\n"
      "    \"accounts.txt\" for printing\n"
      "2 - update an account\n"
      "3 - add a new account\n"
      "4 - delete an account\n"
      "5 - end program\n? ");

   unsigned int menuChoice; // variable to store user's choice
   scanf("%u", &menuChoice); // receive choice from user

   return (TransactionAction) menuChoice;
}

void textFile(FILE *readPtr, char *const fileName)
{
   FILE *writePtr;

   if ((writePtr = fopen(fileName, "w")) == NULL)
   {
      printf("File %s could not be opened.", fileName);
   }
   else
   {
      rewind(readPtr);  // sets pointer to beginnig of file
      fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
              "Acct", "Last name", "First name", "Balance");

      // copy all records from random-access file into text file
      while (!feof(readPtr))
      {
         ClientData client = getBlankClient();
         int result = fread(&client, sizeof(ClientData), 1, readPtr);
         if (result != 0 && client.accountNumber != 0)
         {
            fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n",
                    client.accountNumber,
                    client.lastName,
                    client.firstName,
                    client.balance);
         }
      }

      fclose(writePtr);
   }
}

void updateRecord(FILE *fPtr)
{
   // obtain number of account to update
   printf("%s", "Enter account to update (1 - 100): ");
   unsigned int account;
   scanf("%d", &account);
   resetAccountPosition(fPtr, account);

   ClientData client = getBlankClient();

   // read record from file
   fread(&client, sizeof(ClientData), 1, fPtr);

   if (client.accountNumber == 0)
   {
      printf("Account #%d has no information.\n", account);
   }
   else
   {
      // update record
      printClient(&client);

      // request transaction amount from user
      printf("%s", "Enter charge (+) or payment (-): ");
      double transaction;
      scanf("%lf", &transaction);
      client.balance += transaction;
      printClient(&client);
      resetAccountPosition(fPtr, account);

      // write updated record over old record in file
      fwrite(&client, sizeof(ClientData), 1, fPtr);
   }
}

void newRecord(FILE *fPtr)
{
   printf("%s", "Enter new account number (1 - 100): ");
   unsigned int accountNum;
   scanf("%d", &accountNum);
   resetAccountPosition(fPtr, accountNum);
   ClientData client = getBlankClient();
   fread(&client, sizeof(ClientData), 1, fPtr);

   if (client.accountNumber != 0)
   {
      printf("Account #%d already contains information.\n", client.accountNumber);
   }
   else
   {
      // create record
      printf("%s", "Enter lastname, firstname, balance\n? ");
      scanf("%14s%9s%lf",
            &client.lastName, &client.firstName, &client.balance);
      client.accountNumber = accountNum;
      resetAccountPosition(fPtr, client.accountNumber - 1);
      fwrite(&client, sizeof(ClientData), 1, fPtr);
   }
}

void deleteRecord(FILE *fPtr)
{
   printf("%s", "Enter account number to delete (1 - 100): ");
   unsigned int accountNumber;
   scanf("%d", &accountNumber);
   resetAccountPosition(fPtr, accountNumber);

   ClientData client;
   fread(&client, sizeof(ClientData), 1, fPtr);

   if (client.accountNumber == 0)
   {
      printf("Account %d does not exist.\n", accountNumber);
   }
   else
   {
      resetAccountPosition(fPtr, accountNumber);
      ClientData blankClient = getBlankClient();
      fwrite(&blankClient, sizeof(ClientData), 1, fPtr);
   }
}

static inline void printClient(const ClientData *ptrClient)
{
   printf("%-6d%-16s%-11s%10.2f",
          ptrClient->accountNumber,
          ptrClient->lastName,
          ptrClient->firstName,
          ptrClient->balance);
}

static inline ClientData getBlankClient()
{
   ClientData blankClient = {0, "", "", 0.0};
   return blankClient;
}

static inline void resetAccountPosition(FILE *fPtr, unsigned int accountNumber)
{
   fseek(fPtr, (accountNumber - 1) * sizeof(ClientData), SEEK_SET);
}
