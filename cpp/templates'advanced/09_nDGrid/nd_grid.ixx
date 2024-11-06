export module nd_grid;

import std;

export
template <typename T, std::size_t N>
class NDGrid final
{
public:
   explicit NDGrid(const std::size_t size = defaultSize)
   {
      resize(size);
   }

   NDGrid<T, N - 1>& operator[](std::size_t index)
   {
      return elements_[index];
   }

   const NDGrid<T, N - 1>& operator[](std::size_t index) const
   {
      return elements_[index];
   }

   void resize(std::size_t newSize)
   {
      elements_.resize(newSize, NDGrid<T, N - 1>{newSize});
   }

   std::size_t getSize() const
   {
      return elements_.size();
   }

   static constexpr std::size_t defaultSize{10};

private:
   std::vector<NDGrid<T, N - 1>> elements_;
};

export
template <typename T>
class NDGrid<T, 1> final
{
public:
   explicit NDGrid(const std::size_t size = defaultSize)
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
