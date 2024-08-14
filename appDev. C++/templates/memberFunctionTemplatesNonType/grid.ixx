export module grid;

import std;

export
template <typename T, std::size_t Width = 10, std::size_t Height = 10>
class Grid
{
public:
   Grid() = default;

   virtual ~Grid() = default;

   // Explicitly default a copy constructor and copy assignment operator.
   Grid(const Grid& src) = default;

   Grid& operator=(const Grid& rhs) = default;

   // Explicitly default a move constructor and move assignment operator.
   Grid(Grid&& src) = default;

   Grid& operator=(Grid&& rhs) = default;

   template <typename E, std::size_t Width2, std::size_t Height2>
   Grid(const Grid<E, Width2, Height2>& src);

   template <typename E, std::size_t Width2, std::size_t Height2>
   Grid& operator=(const Grid<E, Width2, Height2>& rhs);

   void swap(Grid& other) noexcept;

   std::optional<T>& at(std::size_t x, std::size_t y);

   const std::optional<T>& at(std::size_t x, std::size_t y) const;

   std::size_t getHeight() const
   {
      return Height;
   }

   std::size_t getWidth() const
   {
      return Width;
   }

private:
   void verifyCoordinate(std::size_t x, std::size_t y) const;

   std::optional<T> cells_[Width][Height];
};

template <typename T, std::size_t Width, std::size_t Height>
void Grid<T, Width, Height>::verifyCoordinate(std::size_t x, std::size_t y) const
{
   if (x >= Width)
   {
      throw std::out_of_range{std::format("x ({}) must be less than width ({}).", x, Width)};
   }

   if (y >= Height)
   {
      throw std::out_of_range{std::format("y ({}) must be less than height ({}).", y, Height)};
   }
}

template <typename T, std::size_t Width, std::size_t Height>
const std::optional<T>& Grid<T, Width, Height>::at(std::size_t x, std::size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x][y];
}

template <typename T, std::size_t Width, std::size_t Height>
std::optional<T>& Grid<T, Width, Height>::at(std::size_t x, std::size_t y)
{
   return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

template <typename T, std::size_t Width, std::size_t Height>
template <typename E, std::size_t Width2, std::size_t Height2>
Grid<T, Width, Height>::Grid(const Grid<E, Width2, Height2>& src)
{
   for (std::size_t i{0}; i < Width; ++i)
   {
      for (std::size_t j{0}; j < Height; ++j)
      {
         if (i < Width2 && j < Height2)
         {
            cells_[i][j] = src.at(i, j);
         }
         else
         {
            cells_[i][j].reset();
         }
      }
   }
}

template <typename T, std::size_t Width, std::size_t Height>
void Grid<T, Width, Height>::swap(Grid& other) noexcept
{
   std::swap(cells_, other.cells_);
}

template <typename T, std::size_t Width, std::size_t Height>
template <typename E, std::size_t Width2, std::size_t Height2>
Grid<T, Width, Height>& Grid<T, Width, Height>::operator=(const Grid<E, Width2, Height2>& rhs)
{
   // Copy-and-swap idiom
   Grid<T, Width, Height> temp{rhs}; // Do all the work in a temporary instance.
   swap(temp); // Commit the work with only non-throwing operations.
   return *this;
}
