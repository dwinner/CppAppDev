#pragma once

namespace stacksample
{
   /**
    * \brief Stack item
    */
   typedef unsigned long Item;

   class Stack
   {
   public:
      Stack();
      bool is_empty() const;
      bool is_full() const;

      /**
       * \brief Add item to stack
       * \param item An item to push
       * \return returns false if stack already is full, true otherwise
       */
      bool push(const Item& item);

      /**
       * \brief Pop top into item
       * \param item An item to pop
       * \return returns false if stack already is empty, true otherwise
       */
      bool pop(Item& item);

   private:
      enum { max = 10 }; // constant specific to class
      Item items_[max]; // holds stack items
      int top_; // index for top stack item
   };
}
