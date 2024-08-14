export module grid:implementation;

import :definition;
import std;

export
template <typename T>
Grid<T>::Grid(std::size_t width, std::size_t height)
   : width_{width},
     height_{height}
{
   cells_.resize(width_ * height_);
}

export
template <typename T>
void Grid<T>::verifyCoordinate(std::size_t x, std::size_t y) const
{
   if (x >= width_)
   {
      throw std::out_of_range{std::format("x ({}) must be less than width ({}).", x, width_)};
   }
   if (y >= height_)
   {
      throw std::out_of_range{std::format("y ({}) must be less than height ({}).", y, height_)};
   }
}

export
template <typename T>
const std::optional<T>& Grid<T>::at(std::size_t x, std::size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x + y * width_];
}

export
template <typename T>
std::optional<T>& Grid<T>::at(std::size_t x, std::size_t y)
{
   return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}
