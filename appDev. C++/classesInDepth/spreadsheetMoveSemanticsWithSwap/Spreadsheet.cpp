#include <iostream>
#include <format>
#include "Spreadsheet.hpp"

using namespace std;

Spreadsheet::Spreadsheet(size_t width, size_t height)
    : _width{width}, _height{height}
{
   cout << format("Normal constructor") << endl;

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
   cout << format("Copy constructor") << endl;

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

Spreadsheet &Spreadsheet::operator=(const Spreadsheet &rhs)
{
   cout << format("Copy assignment operator") << endl;

   // Copy-and-swap idiom
   Spreadsheet temp{rhs}; // Do all the work in a temporary instance
   swap(temp); // Commit the work with only non-throwing operations

   return *this;
}

// Move constructor
Spreadsheet::Spreadsheet(Spreadsheet &&src) noexcept
{
   cout << format("Move constructor") << endl;

   swap(src);
}

// Move assignment operator
Spreadsheet &Spreadsheet::operator=(Spreadsheet &&rhs) noexcept
{
   cout << format("Move assignment operator") << endl;

   auto moved{std::move(rhs)}; // Move rhs into moved (noexcept)
   swap(moved); // Commit the work with only non-throwing operations

   return *this;
}
