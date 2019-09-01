/**
 * The queue interface implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue_iface.h"

/* local functions */
static void copyToNode(Item item, Node* nodePtr);
static void copyToItem(Node* nodePtr, Item* itemPtr);

void initializeQueue(Queue* queuePtr)
{
   queuePtr->front = queuePtr->rear = NULL;
   queuePtr->items = 0;
}

bool queueIsFull(const Queue* queuePtr)
{
   return queuePtr->items == MAX_QUEUE;
}

bool queueIsEmpty(const Queue* queuePtr)
{
   return queuePtr->items == 0;
}

int queueItemCount(const Queue* queuePtr)
{
   return queuePtr->items;
}

bool enqueue(const Item item, Queue* queuePtr)
{
   if (queueIsFull(queuePtr))
   {
      return false;
   }

   Node* new_node_ptr = (Node*)malloc(sizeof(Node));
   if (new_node_ptr == NULL)
   {
      fprintf(stderr, "Unable to allocate memory!\n");
      exit(EXIT_FAILURE);
   }

   copyToNode(item, new_node_ptr);
   new_node_ptr->next = NULL;

   if (queueIsEmpty(queuePtr))
   {
      queuePtr->front = new_node_ptr; /* item goes to front */
   }
   else
   {
      queuePtr->rear->next = new_node_ptr; /* link at end of queue */
   }

   queuePtr->rear = new_node_ptr; /* record location of end */
   queuePtr->items++; /* one more item in queue */

   return true;
}

bool dequeue(Item* itemPtr, Queue* queuePtr)
{
   if (queueIsEmpty(queuePtr))
   {
      return false;
   }

   copyToItem(queuePtr->front, itemPtr);
   Node* node_to_del = queuePtr->front;
   queuePtr->front = queuePtr->front->next;
   free(node_to_del);
   queuePtr->items--;
   if (queuePtr->items == 0)
   {
      queuePtr->rear = NULL;
   }

   return true;
}

void cleanQueue(Queue* queuePtr)
{
   Item dummy;
   while (!queueIsEmpty(queuePtr))
   {
      dequeue(&dummy, queuePtr);
   }
}

static void copyToNode(const Item item, Node* nodePtr)
{
   nodePtr->item = item;
}

static void copyToItem(Node* nodePtr, Item* itemPtr)
{
   *itemPtr = nodePtr->item;
}
