/**
 * A simple stack program
 */

#include <stdlib.h>
#include <stdio.h>
#include "stack_iface.h"

static void instructions();

int main()
{
   StackNode* stackPtr = NULL; // points to stack top
   int value; // int input by user

   instructions(); // display the menu
   printf("%s", "? ");
   unsigned int choice; // user's menu choice
   scanf_s("%u", &choice);

   // while user does not enter 3
   while (choice != 3)
   {
      switch (choice)
      {
         // push value onto stack
      case 1:
         printf("%s", "Enter an integer: ");
         scanf_s("%d", &value);
         if (push(stackPtr, value))
         {
            printStack(stackPtr);
         }
         else
         {
            printf("%d not inserted. No memory available.\n", value);
         }

         break;

         // pop value off stack
      case 2:
         // if stack is not empty
         if (!isEmpty(stackPtr))
         {
            printf("The popped value is %d.\n", pop(stackPtr));
         }

         printStack(stackPtr);
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

   return EXIT_SUCCESS;
}

/**
 * \brief Display program instructions to user
 */
void instructions()
{
   puts("Enter choice:\n"
      "1 to push a value on the stack\n"
      "2 to pop a value off the stack\n"
      "3 to end program");
}
