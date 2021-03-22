#include "Stack.h"

namespace stacksample
{
   Stack::Stack() // create an empty stack
   {
      top_ = 0;
   }

   bool Stack::is_empty() const
   {
      return top_ == 0;
   }

   bool Stack::is_full() const
   {
      return top_ == max;
   }

   bool Stack::push(const Item& item)
   {
      if (top_ < max)
      {
         items_[top_++] = item;
         return true;
      }

      return false;
   }

   bool Stack::pop(Item& item)
   {
      if (top_ > 0)
      {
         item = items_[--top_];
         return true;
      }

      return false;
   }
}
