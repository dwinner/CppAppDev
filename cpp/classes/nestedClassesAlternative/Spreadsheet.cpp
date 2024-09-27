#include <algorithm>
#include <stdexcept>
#include <format>
#include <string>
#include "Spreadsheet.hpp"

using namespace std;

Spreadsheet::Spreadsheet(size_t width,
                         size_t height,
                         const SpreadsheetApplication &anApp)
    : _id{_counter++},
      _width{min(width, MaxWidth)},
      _height{min(height, MaxHeight)},
      _app{anApp}
{
   _cells = new Cell *[_width];
   for (size_t i{0}; i < _width; ++i)
   {
      _cells[i] = new Cell[_height];
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
    : Spreadsheet{src._width, src._height, src._app}
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

void Spreadsheet::setCellAt(size_t x, size_t y, const Cell &cell)
{
   verifyCoordinate(x, y);
   _cells[x][y] = cell;
}

const Spreadsheet::Cell &Spreadsheet::getCellAt(size_t x, size_t y) const
{
   verifyCoordinate(x, y);
   return _cells[x][y];
}

Spreadsheet::Cell &Spreadsheet::getCellAt(size_t x, size_t y)
{
   return const_cast<Spreadsheet::Cell &>(as_const(*this).getCellAt(x, y));
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

size_t Spreadsheet::getId() const
{
   return _id;
}

Spreadsheet::Cell::Cell(double initialValue)
    : _value{initialValue}
{
}

Spreadsheet::Cell::Cell(string_view initialValue)
    : _value{stringToDouble(initialValue)}
{
}

void Spreadsheet::Cell::set(double value)
{
   _value = value;
}

double Spreadsheet::Cell::getValue() const
{
   return _value;
}

void Spreadsheet::Cell::set(string_view value)
{
   _value = stringToDouble(value);
}

string Spreadsheet::Cell::getString() const
{
   return doubleToString(_value);
}

string Spreadsheet::Cell::doubleToString(double value) const
{
   return to_string(value);
}

double Spreadsheet::Cell::stringToDouble(string_view value) const
{
   double number{0};
   from_chars(value.data(), value.data() + value.size(), number);
   return number;
}