#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>

/**
 * Provides simple round-robin semantics for a list of elements.
 * @tparam T element's type
 */
template <typename T>
class RoundRobin final
{
public:
   /**
    * Ctor.
    * @brief Client can give a hint as to the number of expected elements for increased efficiency.
    * @param numExpected Number of elements
    */
   explicit RoundRobin(std::size_t numExpected = 0);

   // Prevent copy construction and copy assignment
   RoundRobin(const RoundRobin& src) = delete;

   RoundRobin& operator=(const RoundRobin& rhs) = delete;

   // Explicitly default a move constructor and move assignment operator
   RoundRobin(RoundRobin&& src) noexcept = default;

   RoundRobin& operator=(RoundRobin&& rhs) noexcept = default;

   /**
    * @brief Appends element to the end of the list.
    * Always add the new element at the end.
    * @details May be called between calls to getNext().
    * @param element Element to add
    */
   void add(const T& element);

   /**
    * @brief Removes the first (and only the first) element
    * in the list that is equal (with operator==) to element.
    * May be called between calls to getNext().
    * @param element Element to remove
    */
   void remove(const T& element);

   /**
    * @brief Returns the next element in the list, starting with the first,
    * and cycling back to the first when the end of the list is
    * reached, taking into account elements that are added or removed.
    * @return The next element.
    */
   T& getNext();

private:
   std::vector<T> elements_;
   typename std::vector<T>::iterator nextElement_;
};

template<typename T>
T &RoundRobin<T>::getNext()
{
   // First, make sure there are elements.
   if (elements_.empty()) {
      throw std::out_of_range{ "No elements in the list" };
   }

   // Store the current element which we need to return.
   auto& toReturn{ *nextElement_ };

   // Increment the iterator modulo the number of elements.
   ++nextElement_;
   if (nextElement_ == end(elements_))
   {
      nextElement_ = begin(elements_);
   }

   // Return a reference to the element.
   return toReturn;
}

template<typename T>
void RoundRobin<T>::remove(const T &element)
{
   for (auto it{ begin(elements_) };
   it != end(elements_);
   ++it)
   {
      if (*it == element) {
         // Removing an element invalidates the nextElement iterator
         // if it refers to an element past the point of the removal.
         // Take advantage of the random-access features of the iterator
         // to track the position of the current element after removal.
         std::ptrdiff_t newPos;

         if (nextElement_ == end(elements_) - 1 && nextElement_ == it)
         {
            // nextElement refers to the last element in the list,
            // and we are removing that last element, so wrap back to
            // the beginning.
            newPos = 0;
         } else if (nextElement_ <= it)
         {
            // Otherwise, if nextElement is before or at the one
            // we're removing, the new position is the same as before.
            newPos = nextElement_ - begin(elements_);
         } else {
            // Otherwise, it's one less than before.
            newPos = nextElement_ - begin(elements_) - 1;
         }

         // Erase the element (and ignore the return value).
         elements_.erase(it);

         // Now reset our iterator to make sure it is valid.
         nextElement_ = begin(elements_) + newPos;

         return;
      }
   }
}

template<typename T>
void RoundRobin<T>::add(const T &element)
{
   // Even though we add the element at the end, the vector could
   // reallocate and invalidate the nextElement iterator with
   // the push_back() call. Take advantage of the random-access
   // iterator features to save our spot.
   // Note: ptrdiff_t is a type capable of storing the difference
   //       between two random-access iterators.
   std::ptrdiff_t pos{ nextElement_ - begin(elements_) };

   // Add the element.
   elements_.push_back(element);

   // Reset our iterator to make sure it is valid.
   nextElement_ = begin(elements_) + pos;
}

template<typename T>
RoundRobin<T>::RoundRobin(std::size_t numExpected)
{
   // If the client gave a guideline, reserve that much space.
   elements_.reserve(numExpected);

   // Initialize m_nextElement even though it isn't used until
   // there's at least one element.
   nextElement_ = begin(elements_);
}
