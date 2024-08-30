#ifndef POLYMORPHICSPREADSHEET_STRINGSPREADSHEETCELL_HPP
#define POLYMORPHICSPREADSHEET_STRINGSPREADSHEETCELL_HPP

#include <string>
#include <optional>
#include "DoubleSpreadsheetCell.hpp"

class StringSpreadsheetCell : public SpreadsheetCell
{
public:
   StringSpreadsheetCell() = default;

   StringSpreadsheetCell(const DoubleSpreadsheetCell &cell)
       : _value{cell.getString()}
   {
   }

   void set(std::string_view value) override
   {
      _value = value;
   }

   std::string getString() const override
   {
      return _value.value_or("");
   }

private:
   std::optional<std::string> _value;
};

StringSpreadsheetCell operator+(const StringSpreadsheetCell &lhs, const StringSpreadsheetCell &rhs)
{
   StringSpreadsheetCell newCell;
   newCell.set(lhs.getString() + rhs.getString());
   return newCell;
}


#endif //POLYMORPHICSPREADSHEET_STRINGSPREADSHEETCELL_HPP
