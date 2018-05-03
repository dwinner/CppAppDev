/**
 * Interface for a queue
 */
#ifndef QUEUE_IFACE_H
#define QUEUE_IFACE_H

#include <stdbool.h>

/**
 * \brief Item to be processed
 */
typedef struct item
{
   /**
    * \brief The time when a customer joins the queue
    */
   long arrive;

   /**
    * \brief The number of consultation minutes desired
    */
   int processTime;
} Item;

/**
 * \brief Maximum elements in the queue
 */
#define MAX_QUEUE 10

/**
 * \brief Node for a queue
 */
typedef struct node
{
   /**
    * \brief Item for a queue
    */
   Item item;

   /**
    * \brief The next queue node ponter
    */
   struct node* next;
} Node;

/**
 * \brief Queue
 */
typedef struct queue
{
   /**
    * \brief Pointer to front of the queue
    */
   Node* front;

   /**
    * \brief Ponter to rear of queue
    */
   Node* rear;

   /**
    * \brief Number of items in queue
    */
   int items;
} Queue;

/**
 * \brief Initialize the queue
 * \details Queue is initialized to being empty
 * \param queuePtr Pointer to the queue
 */
void initializeQueue(Queue* queuePtr);

/**
 * \brief Check if queue is full
 * \details Points to previously initialized queue
 * \param queuePtr Pointer to the queue
 * \return true if queue is full, false - otherwise
 */
bool queueIsFull(const Queue* queuePtr);

/**
 * \brief Check if queue is empty
 * \param queuePtr Pointer to the previously initialized queue
 * \return true if queue is empty, false - otherwise
 */
bool queueIsEmpty(const Queue* queuePtr);

/**
 * \brief Determine number of items in queue
 * \param queuePtr Pointer to the previously initialized queue
 * \return Number of items in queue
 */
int queueItemCount(const Queue* queuePtr);

/**
 * \brief Add item to rear of queue
 * \param item Item to be placed at rear of queue
 * \param queuePtr Pointer to the previously initialized queue
 * \return true, if queue isn't empty and item is placed at rear of the queue,
 *    false - otherwise, and queue is unchanged
 */
bool enqueue(Item item, Queue* queuePtr);

/**
 * \brief Remove item from front of queue
 * \param itemPtr 
 * \param queuePtr Pointer to the previously initialized queue
 * \return  if queue is not empty, item at head of queue is copied to itemPtr
 *          and deleted from queue, and function returns true; if the operation
 *          empties the queue, the queue is reset to empty. If the queue is empty to
 *          begin with, queue is unchanged and the function returns false
 */
bool dequeue(Item* itemPtr, Queue* queuePtr);

/**
 * \brief Clean the queue
 * \param queuePtr Pointer to the previously initialized queue
 */
void cleanQueue(Queue* queuePtr);

#endif // QUEUE_IFACE_H
