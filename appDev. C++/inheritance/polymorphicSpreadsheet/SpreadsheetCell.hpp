#ifndef POLYMORPHICSPREADSHEET_SPREADSHEETCELL_HPP
#define POLYMORPHICSPREADSHEET_SPREADSHEETCELL_HPP

#include <string_view>

class SpreadsheetCell
{
public:
   virtual ~SpreadsheetCell() = default;

   virtual void set(std::string_view value) = 0;

   virtual std::string getString() const = 0;
};


#endif //POLYMORPHICSPREADSHEET_SPREADSHEETCELL_HPP
