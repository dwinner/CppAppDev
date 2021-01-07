#ifndef TEMPLATE_WITH_DYNAMIC_ALLOC_STACK_H
#define TEMPLATE_WITH_DYNAMIC_ALLOC_STACK_H

template<typename Type>
class Stack
{
private:
   enum
   {
      size = 10   // default size
   };
   int stackSize_;
   Type *items_;  // holds stack items
   int top_;   // index for top stack item
public:
   explicit Stack(int stackSize = size);

   Stack(const Stack &srcStack);

   ~Stack()
   {
      delete[] items_;
   }

   bool isEmpty()
   {
      return top_ == 0;
   }

   bool isFull()
   {
      return top_ == stackSize_;
   }

   /**
    * Add item to stack
    * @param item item to be added
    * @return true if ok, false - otherwise
    */
   bool push(const Type &item);

   /**
    * Pop top into item
    * @param item item to be popped
    * @return true if ok, false - otherwise
    */
   bool pop(Type &item);

   Stack &operator=(const Stack &srcStack);
};

template<typename Type>
Stack<Type>::Stack(int stackSize)
   : stackSize_(stackSize),
     top_(0)
{
   items_ = new Type[stackSize];
}

template<typename Type>
Stack<Type>::Stack(const Stack &srcStack)
{
   stackSize_ = srcStack.stackSize_;
   top_ = srcStack.top_;
   items_ = new Type[stackSize_];
   for (int i = 0; i < top_; ++i)
   {
      items_[i] = srcStack.items_[i];
   }
}

template<typename Type>
bool Stack<Type>::push(const Type &item)
{
   if (top_ < stackSize_)
   {
      items_[top_++] = item;
      return true;
   }
   else
   {
      return false;
   }
}

template<typename Type>
bool Stack<Type>::pop(Type &item)
{
   if (top_ > 0)
   {
      item = items_[--top_];
      return true;
   }
   else
   {
      return false;
   }
}

template<typename Type>
Stack<Type> &Stack<Type>::operator=(const Stack &srcStack)
{
   if (this == &srcStack)
   {
      return *this;
   }

   delete[] items_;
   stackSize_ = srcStack.stackSize_;
   top_ = srcStack.top_;
   items_ = new Type[stackSize_];
   for (int i = 0; i < top_; ++i)
   {
      items_[i] = srcStack.items_[i];
   }

   return *this;
}


#endif //TEMPLATE_WITH_DYNAMIC_ALLOC_STACK_H
