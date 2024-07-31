#ifndef POLYMORPHICSPREADSHEET_DOUBLESPREADSHEETCELL_HPP
#define POLYMORPHICSPREADSHEET_DOUBLESPREADSHEETCELL_HPP

#include <charconv>
#include <optional>
#include <string>
#include "SpreadsheetCell.hpp"

class DoubleSpreadsheetCell : public SpreadsheetCell
{
public:
   virtual void set(double value)
   {
      _value = value;
   }

   virtual double getValue() const
   {
      return _value.value_or(0);
   }

   void set(std::string_view value) override
   {
      _value = stringToDouble(value);
   }

   std::string getString() const override
   {
      return (_value.has_value() ? doubleToString(_value.value()) : "");
   }

private:
   static std::string doubleToString(double value)
   {
      return std::to_string(value);
   }

   static double stringToDouble(std::string_view value)
   {
      double number{0};
      std::from_chars(value.data(), value.data() + value.size(), number);
      return number;
   }

   std::optional<double> _value;
};

DoubleSpreadsheetCell operator+(const DoubleSpreadsheetCell &lhs, const DoubleSpreadsheetCell &rhs)
{
   DoubleSpreadsheetCell newCell;
   newCell.set(lhs.getValue() + rhs.getValue());
   return newCell;
}


#endif //POLYMORPHICSPREADSHEET_DOUBLESPREADSHEETCELL_HPP
