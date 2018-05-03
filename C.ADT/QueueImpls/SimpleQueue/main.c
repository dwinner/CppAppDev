/**
 * Operating and maintaining a queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \brief Self-referential structure
 */
struct queueNode
{
   /**
    * \brief Define data as a char
    */
   char data;

   /**
    * \brief queueNode pointer
    */
   struct queueNode* nextPtr;
};

typedef struct queueNode QueueNode;
typedef QueueNode* QueueNodePtr;

/* Function prototypes */

void printQueue(QueueNodePtr currentPtr);
bool isEmpty(QueueNodePtr headPtr);
char dequeue(QueueNodePtr* headPtr, QueueNodePtr* tailPtr);
bool enqueue(QueueNodePtr* headPtr, QueueNodePtr* tailPtr, char value);
void instructions();

int main(void)
{
   QueueNodePtr head_ptr = NULL; // initialize headPtr
   QueueNodePtr tail_ptr = NULL; // initialize tailPtr
   char item; // char input by user

   instructions(); // display the menu
   printf("%s", "? ");
   unsigned int choice; // user's menu choice
   scanf_s("%u", &choice);

   // while user does not enter 3
   while (choice != 3)
   {
      switch (choice)
      {
      case 1: // enqueue value
         printf("%s", "Enter a character: ");
         scanf_s("\n%c", &item); // BUG: In scanning characters
         if (enqueue(&head_ptr, &tail_ptr, item))
         {
            printQueue(head_ptr);
         }
         else
         {
            printf("%c not inserted. No memory available.\n", item);
         }

         break;

      case 2: // dequeue value
         // if queue is not empty
         if (!isEmpty(head_ptr))
         {
            item = dequeue(&head_ptr, &tail_ptr);
            printf("%c has been dequeued.\n", item);
         }

         printQueue(head_ptr);
         break;

      default:
         puts("Invalid choice.\n");
         instructions();
         break;
      }

      printf("%s", "? ");
      scanf_s("%u", &choice);
   }

   puts("End of run.");

   return 0;
}

/**
 * \brief Display program instructions to user
 */
void instructions()
{
   printf("Enter your choice:\n"
      "   1 to add an item to the queue\n"
      "   2 to remove an item from the queue\n"
      "   3 to end\n");
}

/**
 * \brief Insert a node at queue tail
 * \param headPtr - Head of the queue
 * \param tailPtr - Tail of the queue
 * \param value - value to enqueue
 */
bool enqueue(QueueNodePtr* headPtr, QueueNodePtr* tailPtr, const char value)
{
   QueueNodePtr newPtr = malloc(sizeof(QueueNode));

   if (newPtr != NULL) // is space available
   {
      newPtr->data = value;
      newPtr->nextPtr = NULL;

      // if empty, insert node at head
      if (isEmpty(*headPtr))
      {
         *headPtr = newPtr;
      }
      else
      {
         (*tailPtr)->nextPtr = newPtr;
      }

      *tailPtr = newPtr;

      return true;
   }

   return false;
}

/**
 * \brief Remove node from the queue head
 * \param headPtr - Head of the queue
 * \param tailPtr - Tail of the queue
 * \return Dequeued node
 */
char dequeue(QueueNodePtr* headPtr, QueueNodePtr* tailPtr)
{
   const char value = (*headPtr)->data;
   QueueNodePtr tempPtr = *headPtr;
   *headPtr = (*headPtr)->nextPtr;

   // if queue is empty
   if (*headPtr == NULL)
   {
      *tailPtr = NULL;
   }

   free(tempPtr);
   return value;
}

/**
 * \brief Finds out whether the queue is empty or not
 * \param headPtr The head of the queue
 * \return true, if queue is empty, false - otherwise
 */
bool isEmpty(QueueNodePtr headPtr)
{
   return headPtr == NULL;
}

/**
 * \brief Print the queue
 * \param currentPtr Starting pointer
 */
void printQueue(QueueNodePtr currentPtr)
{
   // if queue is empty
   if (currentPtr == NULL)
   {
      puts("Queue is empty.\n");
   }
   else
   {
      puts("The queue is:");

      // while not end of queue
      while (currentPtr != NULL)
      {
         printf("%c --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;
      }

      puts("NULL\n");
   }
}
