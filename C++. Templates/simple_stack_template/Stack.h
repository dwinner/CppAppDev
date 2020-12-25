#ifndef SIMPLE_STACK_TEMPLATE_STACK_H
#define SIMPLE_STACK_TEMPLATE_STACK_H

template<typename Type>
class Stack
{
private:
   enum
   {
      max = 10   // constant specific to class
   };
   Type items_[max]; // holds stack items
   int top_;   // index for top stack item

public:
   Stack();

   bool isEmpty();

   bool isFull();

   bool push(const Type &item);  // add item to stack

   bool pop(Type &item);   // pop top into item
};

template<typename Type>
Stack<Type>::Stack()
{
   top_ = 0;
}

template<typename Type>
bool Stack<Type>::isEmpty()
{
   return top_ == 0;
}

template<typename Type>
bool Stack<Type>::isFull()
{
   return top_ == max;
}

template<typename Type>
bool Stack<Type>::push(const Type &item)
{
   if (top_ < max)
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

#endif //SIMPLE_STACK_TEMPLATE_STACK_H
