/**
 * Inserting and deleting nodes in a list
 */

#include "ListNodeInterface.h"
#include <stdio.h>

static void printList(ListNodePtr currentPtr);
static void instructions(void);

enum choice
{
   InsertNode = 1,
   DeleteNode = 2,
   Exit = 3
};

int main()
{
   ListNodePtr startPtr = NULL; // initially there are no nodes
   char item; // char entered by user
   instructions(); // display the menu
   printf("%s", "? ");
   enum choice choice; // user's choice
   scanf("%u", &choice);

   // loop while user does not choose 3
   while (choice != Exit)
   {
      switch (choice)
      {
      case InsertNode:
         printf("%s", "Enter a character: ");
         scanf("\n%c", &item);
         if (insert(&startPtr, item)) // insert item in list
         {
            printList(startPtr);
         }

         break;

      case DeleteNode:
         // if list isn't empty
         if (!isEmpty(startPtr))
         {
            printf("%s", "Enter character to be deleted: ");
            scanf("\n%c", &item);

            // if character is found, remove it
            if (delete(&startPtr, item) != '\0') // remove item
            {
               printf("%c deleted.\n", item);
               printList(startPtr);
            }
            else
            {
               printf("%c not found.\n\n", item);
            }
         }
         else
         {
            puts("List is empty.\n");
         }

         break;

      case Exit:
         goto Exit;

      default:
         puts("Invalid choice.\n");
         instructions();
         break;
      }

      printf("%s", "? ");
      scanf("%u", &choice);
   }

Exit:
   puts("End of run.");
   return EXIT_SUCCESS;
}

/**
 * \brief Print the list
 * \param currentPtr Starting node
 */
static void printList(ListNodePtr currentPtr)
{
   // if list is empty
   if (isEmpty(currentPtr))
   {
      puts("List is empty.\n");
   }
   else
   {
      puts("The list is:");

      // while not the end of the list
      while (currentPtr != NULL)
      {
         printf("%c --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;
      }

      puts("NULL\n");
   }
}

/**
 * \brief Display program instructions to user
 */
static void instructions(void)
{
   puts("Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end.");
}
