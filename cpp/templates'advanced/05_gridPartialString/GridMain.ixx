export module grid:main;

import std;

export
template <typename T, std::size_t Width, std::size_t Height>
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
      throw std::out_of_range{
         std::format("x ({}) must be less than width ({}).", x, Width)
      };
   }

   if (y >= Height)
   {
      throw std::out_of_range{
         std::format("y ({}) must be less than height ({}).", y, Height)
      };
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
