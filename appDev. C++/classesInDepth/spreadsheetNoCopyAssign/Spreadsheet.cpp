#include <stdexcept>
#include <format>
#include "Spreadsheet.hpp"

using namespace std;

Spreadsheet::Spreadsheet(size_t width, size_t height)
    : _width{width},
      _height{height}
{
   _cells = new SpreadsheetCell *[_width];
   for (size_t i{0}; i < _width; ++i)
   {
      _cells[i] = new SpreadsheetCell[_height];
   }
}

Spreadsheet::~Spreadsheet()
{
   for (size_t i{0}; i < _width; ++i)
   {
      delete[] _cells[i];
   }

   delete[] _cells;
   _cells = nullptr;
}

void Spreadsheet::verifyCoordinate(size_t x, size_t y) const
{
   if (x >= _width)
   {
      throw out_of_range{format("x ({}) must be less than width ({}).", x, _width)};
   }

   if (y >= _height)
   {
      throw out_of_range{format("y ({}) must be less than height ({}).", y, _height)};
   }
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell &cell)
{
   verifyCoordinate(x, y);
   _cells[x][y] = cell;
}

SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y)
{
   verifyCoordinate(x, y);
   return _cells[x][y];
}

void Spreadsheet::swap(Spreadsheet &other) noexcept
{
   std::swap(_width, other._width);
   std::swap(_height, other._height);
   std::swap(_cells, other._cells);
}

void swap(Spreadsheet &first, Spreadsheet &second) noexcept
{
   first.swap(second);
}
