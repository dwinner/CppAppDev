#ifndef QUEUE_SAMPLE_QUEUE_H
#define QUEUE_SAMPLE_QUEUE_H

#include "Customer.h"

typedef Customer item;

class Queue
{
public:
   explicit Queue(int queue_size = q_size); // create queue with a qs limit

   ~Queue();

   bool isEmpty() const;

   bool isFull() const;

   int queueCount() const;

   bool enQueue(const item& item); // add item to end

   bool deQueue(item& item); // remove item from front

private:
   // class scope definitions
   // Node is a nested structure definition local to this class
   struct Node
   {
      item item;
      struct Node* next{};
   };

   enum
   {
      q_size = 10
   };

   // private class members
   Node* front_; // pointer to front of Queue
   Node* rear_; // pointer to rear of Queue
   int items_; // current number of items in Queue
   const int qsize_; // maximum number of items in Queue

   // preemptive definitions to prevent public copying
   Queue(const Queue& queue) : qsize_(0)
   {
   }

   Queue& operator=(const Queue& queue)
   {
      return *this;
   }
};

#endif //QUEUE_SAMPLE_QUEUE_H
