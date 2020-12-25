#ifndef SIMPLE_ARRAY_TEMPLATE_ARRAY_H
#define SIMPLE_ARRAY_TEMPLATE_ARRAY_H

#include <iostream>
#include <cstdlib>

template<class T, int size>
class ArrayTP
{
public:
   ArrayTP() = default;

   explicit ArrayTP(const T &anArray);

   virtual T &operator[](int index);

   virtual T operator[](int index) const;

private:
   T array_[size];
};

template<class T, int size>
ArrayTP<T, size>::ArrayTP(const T &anArray)
{
   for (int i = 0; i < size; i++)
   {
      array_[i] = anArray;
   }
}

template<class T, int size>
T &ArrayTP<T, size>::operator[](int index)
{
   if (index < 0 || index >= size)
   {
      std::cerr << "Error in array limits: " << index << " is out of range\n";
      std::exit(EXIT_FAILURE);
   }

   return array_[index];
}

template<class T, int size>
T ArrayTP<T, size>::operator[](int index) const
{
   if (index < 0 || index >= size)
   {
      std::cerr << "Error in array limits: " << index << " is out of range\n";
      std::exit(EXIT_FAILURE);
   }

   return array_[index];
}

#endif //SIMPLE_ARRAY_TEMPLATE_ARRAY_H
