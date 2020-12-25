#include "Queue.h"
#include <cstdlib>

// Queue methods
Queue::Queue(const int queue_size) : qsize_(queue_size)
{
   front_ = rear_ = nullptr; // or nullptr
   items_ = 0;
}

Queue::~Queue()
{
   Node* temp;
   while (front_ != nullptr) // while queue is not yet empty
   {
      temp = front_; // save address of front item
      front_ = front_->next; // reset pointer to next item
      delete temp; // delete former front
   }
}

bool Queue::isEmpty() const
{
   return items_ == 0;
}

bool Queue::isFull() const
{
   return items_ == qsize_;
}

int Queue::queueCount() const
{
   return items_;
}

// Add item to queue
bool Queue::enQueue(const item& item)
{
   if (isFull())
   {
      return false;
   }

   Node* add_node = new Node; // create node

   // on failure, new throws std::bad_alloc exception
   add_node->item = item; // set node pointers
   add_node->next = nullptr; // or nullptr;
   items_++;
   if (front_ == nullptr) // if queue is empty,
   {
      front_ = add_node; // place item at front
   }
   else
   {
      rear_->next = add_node;  // else place at rear
   }

   rear_ = add_node; // have rear point to new node

   return true;
}

// Place front item into item variable and remove from queue
bool Queue::deQueue(item& item)
{
   if (front_ == nullptr)
   {
      return false;
   }

   item = front_->item; // set item to first item in queue
   items_--;
   Node* temp = front_; // save location of first item
   front_ = front_->next; // reset front to next item
   delete temp; // delete former first item
   if (items_ == 0)
   {
      rear_ = nullptr;
   }

   return true;
}
