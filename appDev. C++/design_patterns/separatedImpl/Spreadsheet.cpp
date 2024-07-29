#include <stdexcept>
#include <format>
#include "Spreadsheet.hpp"

using namespace std;

// Spreadsheet::Impl class definition.
class Spreadsheet::Impl
{
public:
   Impl(size_t width, size_t height);

   Impl(const Impl &src);

   Impl(Impl &&) noexcept = default;

   ~Impl();

   Impl &operator=(const Impl &rhs);

   Impl &operator=(Impl &&) noexcept = default;

   void setCellAt(size_t x, size_t y, const SpreadsheetCell &cell);

   SpreadsheetCell &getCellAt(size_t x, size_t y);

   const SpreadsheetCell &getCellAt(size_t x, size_t y) const;

   size_t getId() const;

   void swap(Impl &other) noexcept;

private:
   void verifyCoordinate(size_t x, size_t y) const;

   const size_t _id{0};
   size_t _width{0};
   size_t _height{0};
   SpreadsheetCell **_cells{nullptr};

   static inline size_t _counter{0};
};

// Spreadsheet::Impl member function definitions.
Spreadsheet::Impl::Impl(size_t width, size_t height)
    : _id{_counter++},
      _width{min(width, Spreadsheet::MaxWidth)},
      _height{min(height, Spreadsheet::MaxHeight)}
{
   _cells = new SpreadsheetCell *[_width];
   for (size_t i{0}; i < _width; ++i)
   {
      _cells[i] = new SpreadsheetCell[_height];
   }
}

Spreadsheet::Impl::~Impl()
{
   for (size_t i{0}; i < _width; ++i)
   {
      delete[] _cells[i];
   }

   delete[] _cells;
   _cells = nullptr;
}

Spreadsheet::Impl::Impl(const Impl &src)
    : Impl{src._width, src._height}
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

void Spreadsheet::Impl::verifyCoordinate(size_t x, size_t y) const
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

void Spreadsheet::Impl::setCellAt(size_t x, size_t y, const SpreadsheetCell &cell)
{
   verifyCoordinate(x, y);
   _cells[x][y] = cell;
}

const SpreadsheetCell &Spreadsheet::Impl::getCellAt(size_t x, size_t y) const
{
   verifyCoordinate(x, y);
   return _cells[x][y];
}

SpreadsheetCell &Spreadsheet::Impl::getCellAt(size_t x, size_t y)
{
   return const_cast<SpreadsheetCell &>(as_const(*this).getCellAt(x, y));
}

void Spreadsheet::Impl::swap(Impl &other) noexcept
{
   std::swap(_width, other._width);
   std::swap(_height, other._height);
   std::swap(_cells, other._cells);
}

Spreadsheet::Impl &Spreadsheet::Impl::operator=(const Impl &rhs)
{
   // Copy-and-swap idiom
   Impl temp{rhs}; // Do all the work in a temporary instance
   swap(temp); // Commit the work with only non-throwing operations
   return *this;
}

size_t Spreadsheet::Impl::getId() const
{
   return _id;
}

// Spreadsheet member function definitions.
Spreadsheet::Spreadsheet(size_t width, size_t height)
    : _impl{make_unique<Impl>(width, height)}
{
}

Spreadsheet::Spreadsheet(const Spreadsheet &src)
    : _impl{make_unique<Impl>(*src._impl)}
{
}

Spreadsheet::~Spreadsheet() = default;

Spreadsheet::Spreadsheet(Spreadsheet &&) noexcept = default;

Spreadsheet &Spreadsheet::operator=(Spreadsheet &&) noexcept = default;

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell &cell)
{
   _impl->setCellAt(x, y, cell);
}

const SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) const
{
   return _impl->getCellAt(x, y);
}

SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y)
{
   return _impl->getCellAt(x, y);
}

size_t Spreadsheet::getId() const
{
   return _impl->getId();
}

Spreadsheet &Spreadsheet::operator=(const Spreadsheet &rhs)
{
   *_impl = *rhs._impl;
   return *this;
}

void Spreadsheet::swap(Spreadsheet &other) noexcept
{
   std::swap(_impl, other._impl);
}

void swap(Spreadsheet &first, Spreadsheet &second) noexcept
{
   first.swap(second);
}
