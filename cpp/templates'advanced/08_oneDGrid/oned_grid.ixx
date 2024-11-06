export module oned_grid;

import std;

export
template <typename T>
class OneDGrid final
{
public:
   explicit OneDGrid(const std::size_t size = defaultSize)
   {
      resize(size);
   }

   T& operator[](std::size_t index)
   {
      return elements_[index];
   }

   const T& operator[](std::size_t index) const
   {
      return elements_[index];
   }

   void resize(std::size_t newSize)
   {
      elements_.resize(newSize);
   }

   std::size_t getSize() const
   {
      return elements_.size();
   }

   static constexpr std::size_t defaultSize{10};

private:
   std::vector<T> elements_;
};
