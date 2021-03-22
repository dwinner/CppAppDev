/**
 * Transaction C-style interface
 */

#include <stdio.h>

#ifndef INC_7_TRANSACTION_APP_TRANSACTION_H
#define INC_7_TRANSACTION_APP_TRANSACTION_H

/**
 * Client data structure
 */
typedef struct
{
   /**
    * accountNumber
    */
   unsigned int accountNumber;

   /**
    * Last name (max length = 15 chars)
    */
   char lastName[15];

   /**
    * First name (max length = 10 chars)
    */
   char firstName[10];

   /**
    * Account balance
    */
   double balance;
} ClientData;

/**
 * Transaction action
 */
typedef enum
{
   /**
    * Create file
    */
      CREATE_FILE = 1,

   /**
    * Update record
    */
      UPDATE_RECORD,

   /**
    * New record
    */
      NEW_RECORD,

   /**
    * Delete record
    */
      DELETE_RECORD,

   /**
    * Exit action
    */
      EXIT
} TransactionAction;

/**
 * Enter the choice action
 * @return Transaction action
 */
TransactionAction enterChoice(void);

/**
 * Create new text file
 * @param readPtr File pointer for reading
 * @param fileName File name for printing
 */
void textFile(FILE *readPtr, char *const fileName);

/**
 * Update record
 * @param fPtr File pointer
 */
void updateRecord(FILE *fPtr);

/**
 * Create a new record
 * @param fPtr File pointer
 */
void newRecord(FILE *fPtr);

/**
 * Delete record
 * @param fPtr File pointer
 */
void deleteRecord(FILE *fPtr);

#endif //INC_7_TRANSACTION_APP_TRANSACTION_H
