#ifndef SPREADSHEETDEFAULTARGUMENTS_SPREADSHEET_HPP
#define SPREADSHEETDEFAULTARGUMENTS_SPREADSHEET_HPP

#include <cstddef>
#include "SpreadsheetCell.hpp"

class Spreadsheet
{
public:
   explicit Spreadsheet(std::size_t width = DefaultHeight, std::size_t height = DefaultWeight);

   Spreadsheet(const Spreadsheet &src);

   ~Spreadsheet();

   Spreadsheet &operator=(const Spreadsheet &rhs);

   void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell &cell);

   SpreadsheetCell &getCellAt(std::size_t x, std::size_t y);

   [[nodiscard]] const SpreadsheetCell &getCellAt(std::size_t x, std::size_t y) const;

   void swap(Spreadsheet &other) noexcept;

private:
   static const int DefaultHeight = 100;
   static const int DefaultWeight = 100;

   void verifyCoordinate(std::size_t x, std::size_t y) const;

   std::size_t _width{0};
   std::size_t _height{0};
   SpreadsheetCell **_cells{nullptr};
};

void swap(Spreadsheet &first, Spreadsheet &second) noexcept;


#endif //SPREADSHEETDEFAULTARGUMENTS_SPREADSHEET_HPP
