#ifndef SPREADSHEETNOCOPYASSIGN_SPREADSHEET_HPP
#define SPREADSHEETNOCOPYASSIGN_SPREADSHEET_HPP


#include <cstdlib>
#include "SpreadsheetCell.hpp"

class Spreadsheet
{
public:
   Spreadsheet(std::size_t width, std::size_t height);

   Spreadsheet(const Spreadsheet &src) = delete;

   ~Spreadsheet();

   Spreadsheet &operator=(const Spreadsheet &rhs) = delete;

   void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell &cell);

   SpreadsheetCell &getCellAt(std::size_t x, std::size_t y);

   void swap(Spreadsheet &other) noexcept;

private:
   void verifyCoordinate(std::size_t x, std::size_t y) const;

   std::size_t _width{0};
   std::size_t _height{0};
   SpreadsheetCell **_cells{nullptr};
};

void swap(Spreadsheet &first, Spreadsheet &second) noexcept;


#endif //SPREADSHEETNOCOPYASSIGN_SPREADSHEET_HPP
