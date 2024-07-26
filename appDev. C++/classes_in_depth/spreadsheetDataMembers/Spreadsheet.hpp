#ifndef SPREADSHEETDATAMEMBERS_SPREADSHEET_HPP
#define SPREADSHEETDATAMEMBERS_SPREADSHEET_HPP

#include <cstddef>
#include "SpreadsheetCell.hpp"

class SpreadsheetApplication
{
};

class Spreadsheet
{
public:
   Spreadsheet(
       std::size_t width,
       std::size_t height,
       const SpreadsheetApplication &anApp);

   Spreadsheet(const Spreadsheet &src);

   ~Spreadsheet();

   Spreadsheet &operator=(const Spreadsheet &rhs);

   void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell &cell);

   SpreadsheetCell &getCellAt(std::size_t x, std::size_t y);

   [[nodiscard]] const SpreadsheetCell &getCellAt(std::size_t x, std::size_t y) const;

   [[nodiscard]] std::size_t getId() const;

   void swap(Spreadsheet &other) noexcept;

   static constexpr std::size_t MaxHeight{100};
   static constexpr std::size_t MaxWidth{100};

private:
   void verifyCoordinate(std::size_t x, std::size_t y) const;

   const std::size_t _id{0};
   std::size_t _width{0};
   std::size_t _height{0};
   SpreadsheetCell **_cells{nullptr};

   const SpreadsheetApplication &_theApp;

   //static std::size_t _counter; // Pre C++17
   static inline std::size_t _counter{0}; // Since C++17
};

void swap(Spreadsheet &first, Spreadsheet &second) noexcept;

#endif //SPREADSHEETDATAMEMBERS_SPREADSHEET_HPP
