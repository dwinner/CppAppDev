/**
 * Queue template with a nested class
 */

#ifndef NESTED_CLASS_SAMPLE_QUEUETP_H
#define NESTED_CLASS_SAMPLE_QUEUETP_H


template<class Item>
class QueueTP
{
public:
   QueueTP(int qSize = default_queue_size);

   ~QueueTP();

   bool isEmpty() const
   {
      return itemCount_ == 0;
   }

   bool isFull() const
   {
      return itemCount_ == queueSize_;
   }

   int queueCount() const
   {
      return itemCount_;
   }

   bool enqueue(const Item &item); // add item to end

   bool dequeue(Item &item);       // remove item from front

private:
   enum
   {
      default_queue_size = 10
   };

   // Node is a nested class definition
   class Node
   {
   public:
      Item item;
      Node *next;

      Node(const Item &anItem)
          : item(anItem),
            next(0)
      {
      }
   };

   Node *front;       // pointer to front of Queue
   Node *rear;        // pointer to rear of Queue
   int itemCount_;          // current number of items in Queue
   const int queueSize_;    // maximum number of items in Queue

   QueueTP(const QueueTP &queueToCopy)
       : queueSize_(0)
   {
   }

   QueueTP &operator=(const QueueTP &queueToAssign)
   {
      return *this;
   }
};

// QueueTP methods
template<class Item>
QueueTP<Item>::QueueTP(int qSize) : queueSize_(qSize)
{
   front = rear = 0;
   itemCount_ = 0;
}

template<class Item>
QueueTP<Item>::~QueueTP()
{
   Node *temp;
   while (front != nullptr)      // while queue is not yet empty
   {
      temp = front;       // save address of front item
      front = front->next;// reset pointer to next item
      delete temp;        // delete former front
   }
}

// Add item to queue
template<class Item>
bool QueueTP<Item>::enqueue(const Item &item)
{
   if (isFull())
   {
      return false;
   }

   Node *add = new Node(item);    // create node
   // on failure, new throws std::bad_alloc exception
   itemCount_++;
   if (front == nullptr)   // if queue is empty,
   {
      front = add;        // place item at front
   }
   else  // else place at rear
   {
      rear->next = add;
   }

   rear = add;             // have rear point to new node
   return true;
}

// Place front item into item variable and remove from queue
template<class Item>
bool QueueTP<Item>::dequeue(Item &item)
{
   if (front == nullptr)
   {
      return false;
   }

   item = front->item;     // set item to first item in queue
   itemCount_--;
   Node *temp = front;    // save location of first item
   front = front->next;    // reset front to next item
   delete temp;            // delete former first item
   if (itemCount_ == 0)
   {
      rear = nullptr;
   }

   return true;
}


#endif //NESTED_CLASS_SAMPLE_QUEUETP_H
