﻿export module grid;

import std;

export
template <typename T = int, std::size_t WIDTH = 10, std::size_t HEIGHT = 10>
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
      return HEIGHT;
   }

   std::size_t getWidth() const
   {
      return WIDTH;
   }

private:
   void verifyCoordinate(std::size_t x, std::size_t y) const;

   std::optional<T> cells_[WIDTH][HEIGHT];
};

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(std::size_t x, std::size_t y) const
{
   if (x >= WIDTH)
   {
      throw std::out_of_range{std::format("x ({}) must be less than width ({}).", x, WIDTH)};
   }
   if (y >= HEIGHT)
   {
      throw std::out_of_range{std::format("y ({}) must be less than height ({}).", y, HEIGHT)};
   }
}

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
const std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(std::size_t x, std::size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x][y];
}

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(std::size_t x, std::size_t y)
{
   return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}