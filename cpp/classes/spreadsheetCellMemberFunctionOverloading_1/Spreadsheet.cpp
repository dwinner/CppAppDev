#include <utility>
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

Spreadsheet::Spreadsheet(const Spreadsheet &src)
    : Spreadsheet{src._width, src._height}
{
   // The ctor-initializer of this constructor delegates first to the
   // non-copy constructor to allocate the proper amount of memory.
   // The next step is to copy the data.
   for (size_t i{0}; i < _width; ++i)
   {
      for (size_t j{0}; j < _height; ++j)
      {
         _cells[i][j] = src._cells[i][j];
      }
   }
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

const SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) const
{
   verifyCoordinate(x, y);
   return _cells[x][y];
}

SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y)
{
   return const_cast<SpreadsheetCell &>(as_const(*this).getCellAt(x, y));
   //return const_cast<SpreadsheetCell&>(static_cast<const Spreadsheet&>(*this).getCellAt(x, y)); // Pre C++17
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

Spreadsheet &Spreadsheet::operator=(const Spreadsheet &rhs)
{
   // Copy-and-swap idiom
   Spreadsheet temp{rhs}; // Do all the work in a temporary instance
   swap(temp); // Commit the work with only non-throwing operations

   return *this;
}
