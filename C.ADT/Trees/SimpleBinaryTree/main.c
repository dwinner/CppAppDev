/**
 * Creating and traversing a binary tree
 * preorder, inorder, and postorder
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
 * \brief Tree node
 */
struct treeNode
{
   /**
    * \brief Pointer to left subtree
    */
   struct treeNode* leftPtr;

   /**
    * \brief Tree node data
    */
   int data;

   /**
    * \brief Pointer to right subtree
    */
   struct treeNode* rightPtr;
};

/**
 * \see Tree node
 */
typedef struct treeNode TreeNode;

/**
 * \brief Pointer to tree node
 */
typedef TreeNode* TreeNodePtr;

/**
 * \brief Insert node into tree
 * \param treePtr Pointer to the tree
 * \param value Value to be inserted
 * \return true, if value has been inserted successfully, false - otherwise
 */
bool insertNode(TreeNodePtr* treePtr, int value);

/**
 * \brief Begin inorder traversal of tree
 * \param treePtr Pointer to tree
 * \param traverseAction Traverse function
 */
void inOrder(TreeNodePtr treePtr, void (*traverseAction)(TreeNodePtr treeNodePtr));

/**
 * \brief Begin preorder traversal of tree
 * \param treePtr Pointer to tree
 * \param traverseAction Traverse function
 */
void preOrder(TreeNodePtr treePtr, void (*traverseAction)(TreeNodePtr treeNodePtr));

/**
 * \brief Begin postorder traversal of tree
 * \param treePtr Pointer to tree
 * \param traverseAction Traverse function
 */
void postOrder(TreeNodePtr treePtr, void (*traverseAction)(TreeNodePtr treeNodePtr));

/**
 * \brief Traverse function
 * \param treeNodePtr Pointer to tree root
 */
static void traverseAction(TreeNodePtr treeNodePtr);

int main()
{
   TreeNodePtr rootPtr = NULL; // tree initially empty

   srand(time(NULL));
   puts("The numbers being placed in the tree are:");

   // insert random values between 0 and 14 in the tree
   for (unsigned int i = 1; i <= 10; ++i)
   {
      const int item = rand() % 15;
      printf("%3d", item);
      if (!insertNode(&rootPtr, item))
      {
         printf("\nDuplicated item: %d\n", item);
      }
   }

   // traverse the tree preOrder
   puts("\n\nThe preOrder traversal is:");
   preOrder(rootPtr, traverseAction);

   // traverse the tree inOrder
   puts("\n\nThe inOrder traversal is:");
   inOrder(rootPtr, traverseAction);

   // traverse the tree postOrder
   puts("\n\nThe postOrder traversal is:");
   postOrder(rootPtr, traverseAction);

   return EXIT_SUCCESS;
}

bool insertNode(TreeNodePtr* treePtr, int value)
{
   if (*treePtr == NULL) /* if tree is empty */
   {
      *treePtr = malloc(sizeof(TreeNode));
      if (*treePtr != NULL) /* if memory was allocated, then assign data */
      {
         (*treePtr)->data = value;
         (*treePtr)->rightPtr = (*treePtr)->leftPtr = NULL;

         return true;
      }

      exit(EXIT_FAILURE); /* No memory available */
   }

   /* Tree is not empty */
   if (value < (*treePtr)->data) /* data to insert is less than data in current node */
   {
      return insertNode(&((*treePtr)->leftPtr), value);
   }

   if (value > (*treePtr)->data) /* data to insert is greater than data in current node */
   {
      return insertNode(&((*treePtr)->rightPtr), value);
   }

   /* Ignore duplicates */
   return false;
}

void inOrder(TreeNodePtr treePtr, void (*traverseAction)(TreeNodePtr treeNodePtr))
{
   if (treePtr == NULL)
      return;

   inOrder(treePtr->leftPtr, traverseAction);
   traverseAction(treePtr);
   inOrder(treePtr->rightPtr, traverseAction);
}

void preOrder(TreeNodePtr treePtr, void (*traverseAction)(TreeNodePtr treeNodePtr))
{
   if (treePtr == NULL)
      return;

   traverseAction(treePtr);
   preOrder(treePtr->leftPtr, traverseAction);
   preOrder(treePtr->rightPtr, traverseAction);
}

void postOrder(TreeNodePtr treePtr, void (*traverseAction)(TreeNodePtr treeNodePtr))
{
   if (treePtr == NULL)
      return;

   postOrder(treePtr->leftPtr, traverseAction);
   postOrder(treePtr->rightPtr, traverseAction);
   traverseAction(treePtr);
}

static void traverseAction(TreeNodePtr treeNodePtr)
{
   printf("%3d", treeNodePtr->data);
}
