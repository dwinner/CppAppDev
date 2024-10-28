#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <stdexcept>
#include <format>

template<typename TVal>
class AssocArray final
{
public:
   TVal &operator[](std::string_view key);

   const TVal &operator[](std::string_view key) const;

private:
   class Element
   {
   public:
      explicit Element(std::string key, TVal value)
          : key_{std::move(key)}, value_{std::move(value)}
      {}

      std::string key_;
      TVal value_;
   };

   std::vector<Element> data_;
};

template<typename T>
T &AssocArray<T>::operator[](std::string_view key)
{
   // See if key already exist
   for (auto &element: data_)
   {
      if (element.key_ == key)
      {
         return element.value_;
      }
   }

   // If we arrive here, the key doesn't exist yet, add it
   data_.push_back(Element{std::string{key}, T{}});

   // Return reference to the value we just added
   return data_.back().value_;
}

template<typename T>
const T &AssocArray<T>::operator[](std::string_view key) const
{
   for (auto &element: data_)
   {
      if (element.key_ == key)
      {
         return element.value_;
      }
   }

   throw std::invalid_argument{std::format("Key '{}' doesn't exist.", std::string{key})};
}