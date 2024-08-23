#ifndef SUBSCRIPTINGOPERATOR_ARRAY_HPP
#define SUBSCRIPTINGOPERATOR_ARRAY_HPP


#include <cstddef>
#include <utility>
#include <memory>
#include <stdexcept>

template<typename T>
class Array
{
public:
   // Creates an array with a default size that will grow as needed.
   Array();

   virtual ~Array();

   // Disallow copy constructor and copy assignment.
   Array &operator=(const Array &rhs) = delete;

   Array(const Array &src) = delete;

   // Move constructor and move assignment operator.
   Array(Array &&src) noexcept;

   Array &operator=(Array &&rhs) noexcept;

   T &operator[](std::size_t anIndex);

   const T &operator[](std::size_t anIndex) const;

   // Returns the value at index anIndex. Throws an exception of type
   // out_of_range if index anIndex does not exist in the array.
   const T &getElementAt(std::size_t anIndex) const;

   // Sets the value at index anIndex. If index anIndex is out of range,
   // allocates more space to make it in range.
   void setElementAt(std::size_t anIndex, const T &value);

   // Returns the number of elements in the array.
   std::size_t getSize() const noexcept;

private:
   static constexpr std::size_t AllocSize{4};

   void resize(std::size_t newSize);

   T *elements_{nullptr};

   std::size_t size_{0};
};

template<typename T>
Array<T>::Array()
{
   elements_ = new T[AllocSize]{}; // Elements are zero-initialized!
   size_ = AllocSize;
}

template<typename T>
Array<T>::~Array()
{
   delete[] elements_;
   elements_ = nullptr;
   size_ = 0;
}

template<typename T>
Array<T>::Array(Array &&src) noexcept :
    elements_{std::exchange(src.elements_, nullptr)},
    size_{std::exchange(src.size_, 0)}
{
}

template<typename T>
Array<T> &Array<T>::operator=(Array<T> &&rhs) noexcept
{
   if (this == &rhs)
   {
      return *this;
   }

   delete[] elements_;
   elements_ = std::exchange(rhs.elements_, nullptr);
   size_ = std::exchange(rhs.size_, 0);

   return *this;
}

template<typename T>
void Array<T>::resize(std::size_t newSize)
{
   // Create new bigger array with zero-initialized elements.
   auto newArray{std::make_unique<T[]>(newSize)};

   // The new size is always bigger than the old size (size_).
   for (std::size_t i{0}; i < size_; ++i)
   {
      // Copy the elements from the old array to the new one.
      newArray[i] = elements_[i];
   }

   // Delete the old array, and set the new array.
   delete[] elements_;
   size_ = newSize;
   elements_ = newArray.release();
}

template<typename T>
T &Array<T>::operator[](std::size_t anIndex)
{
   if (anIndex >= size_)
   {
      // Allocate AllocSize past the element the client wants.
      resize(anIndex + AllocSize);
   }

   return elements_[anIndex];
}

template<typename T>
const T &Array<T>::operator[](std::size_t anIndex) const
{
   if (anIndex >= size_)
   {
      throw std::out_of_range{""};
   }

   return elements_[anIndex];
}

/*
template <typename T>
const T& Array<T>::operator[](std::size_t anIndex) const
{
	if (anIndex >= size_) {
		static T nullValue{ T{} };
		return nullValue;
	}
	return elements_[anIndex];
}
*/

template<typename T>
const T &Array<T>::getElementAt(std::size_t anIndex) const
{
   if (anIndex >= size_)
   {
      throw std::out_of_range{""};
   }

   return elements_[anIndex];
}

template<typename T>
void Array<T>::setElementAt(std::size_t anIndex, const T &val)
{
   if (anIndex >= size_)
   {
      // Allocate AllocSize past the element the client wants.
      resize(anIndex + AllocSize);
   }

   elements_[anIndex] = val;
}

template<typename T>
std::size_t Array<T>::getSize() const noexcept
{
   return size_;
}


#endif //SUBSCRIPTINGOPERATOR_ARRAY_HPP
