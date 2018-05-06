/**
 * Tree support functions
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* local data type */
typedef struct pair
{
   Node* parent;
   Node* child;
} Pair;

/* Prototypes for local functions */
static Node* makeNode(const Item* itemPtr);
static bool toLeft(const Item* i1, const Item* i2);
static bool toRight(const Item* i1, const Item* i2);
static void addNode(Node* newNode, Node* root);
static void inOrder(const Node* root, void (*pfun)(Item item));
static Pair seekItem(const Item* itemPtr, const Tree* treePtr);
static void deleteNode(Node** ptr);
static void deleteAllNodes(Node* root);

void initializeTree(Tree* treePtr)
{
   treePtr->root = NULL;
   treePtr->size = 0;
}

bool treeIsEmpty(const Tree* treePtr)
{
   return treePtr->root == NULL;
}

bool treeIsFull(const Tree* treePtr)
{
   return treePtr->size == MAX_ITEMS;
}

int treeItemCount(const Tree* treePtr)
{
   return treePtr->size;
}

bool addItem(const Item* itemPtr, Tree* treePtr)
{
   Node* new_node;

   if (treeIsFull(treePtr))
   {
      fprintf(stderr, "Tree is full\n");
      return false;
   }

   if (seekItem(itemPtr, treePtr).child != NULL)
   {
      fprintf(stderr, "Attempted to add duplicate item\n");
      return false;
   }

   new_node = makeNode(itemPtr); /* points to new node */
   if (new_node == NULL)
   {
      fprintf(stderr, "Couldn't create node\n");
      return false;
   }

   treePtr->size++;

   if (treePtr->root == NULL)
      treePtr->root = new_node;
   else
      addNode(new_node, treePtr->root);

   return true;
}

bool inTree(const Item* itemPtr, const Tree* treePtr)
{
   return seekItem(itemPtr, treePtr).child != NULL;
}

bool deleteItem(const Item* itemPtr, Tree* treePtr)
{
   Pair look;

   look = seekItem(itemPtr, treePtr);
   if (look.child == NULL)
      return false;

   if (look.parent == NULL)
      deleteNode(&treePtr->root);
   else if (look.parent->left == look.child)
      deleteNode(&look.parent->left);
   else
      deleteNode(&look.parent->right);

   treePtr->size--;
   return true;
}

void traverse(const Tree* treePtr, void (* funPtr)(Item item))
{
   if (treePtr != NULL)
   {
      inOrder(treePtr->root, funPtr);
   }
}

void deleteAll(Tree* treePtr)
{
   if (treePtr != NULL)
   {
      deleteAllNodes(treePtr->root);
   }

   treePtr->root = NULL;
   treePtr->size = 0;
}

/* local functions */

static void inOrder(const Node* root, void (* pfun)(Item item))
{
   if (root != NULL)
   {
      inOrder(root->left, pfun);
      (*pfun)(root->item);
      inOrder(root->right, pfun);
   }
}

static void deleteAllNodes(Node* root)
{
   Node* pRight;

   if (root != NULL)
   {
      pRight = root->right;
      deleteAllNodes(root->left);
      free(root);
      deleteAllNodes(pRight);
   }
}

static void addNode(Node* newNode, Node* root)
{
   if (toLeft(&newNode->item, &root->item))
   {
      if (root->left == NULL)
         root->left = newNode;
      else
         addNode(newNode, root->left);
   }
   else if (toRight(&newNode->item, &root->item))
   {
      if (root->right == NULL)
         root->right = newNode;
      else
         addNode(newNode, root->right);
   }
   else
   {
      fprintf(stderr, "location error in addNode\n");
      exit(EXIT_FAILURE);
   }
}

static bool toLeft(const Item* i1, const Item* i2)
{
   int comp1;
   return (comp1 = strcmp(i1->petname, i2->petname)) < 0
             ? true
             : comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0;
}

static bool toRight(const Item* i1, const Item* i2)
{
   int comp1;
   return (comp1 = strcmp(i1->petname, i2->petname)) > 0
             ? true
             : comp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0;
}

static Node* makeNode(const Item* itemPtr)
{
   Node* new_node;
   new_node = (Node*)malloc(sizeof(Node));
   if (new_node != NULL)
   {
      new_node->item = *itemPtr;
      new_node->left = new_node->right = NULL;
   }

   return new_node;
}

static Pair seekItem(const Item* itemPtr, const Tree* treePtr)
{
   Pair look;
   look.parent = NULL;
   look.child = treePtr->root;

   if (look.child == NULL)
      return look;

   while (look.child != NULL)
   {
      if (toLeft(itemPtr, &(look.child->item)))
      {
         look.parent = look.child;
         look.child = look.child->left;
      }
      else if (toRight(itemPtr, &(look.child->item)))
      {
         look.parent = look.child;
         look.child = look.child->right;
      }
      else /* must be same if not to left or right */
         break; /* look.child is address of node with item */
   }

   return look;
}

static void deleteNode(Node** ptr) /* ptr is address of parent member pointing to target node */
{
   Node* temp;

   //puts((*ptr)->item.petname);
   if ((*ptr)->left == NULL)
   {
      temp = *ptr;
      *ptr = (*ptr)->right;
      free(temp);
   }
   else if ((*ptr)->right == NULL)
   {
      temp = *ptr;
      *ptr = (*ptr)->left;
      free(temp);
   }
   else /* deleted node has two children */
   {
      /* find where to reattach right subtree */
      for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right);
      temp->right = (*ptr)->right;
      temp = *ptr;
      *ptr = (*ptr)->left;
      free(temp);
   }
}
