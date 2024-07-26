#ifndef SPREADSHEETCELLCONSTMEMBERFUNCTIONS_SPREADSHEETCELL_HPP
#define SPREADSHEETCELLCONSTMEMBERFUNCTIONS_SPREADSHEETCELL_HPP

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
   SpreadsheetCell() = default;

   SpreadsheetCell(double initialValue);

   SpreadsheetCell(std::string_view initialValue);

   void setValue(double value);

   double getValue() const;

   void setString(std::string_view value);

   std::string getString() const;

private:
   static std::string doubleToString(double value);

   static double stringToDouble(std::string_view value);

   double _value{0};
};


#endif //SPREADSHEETCELLCONSTMEMBERFUNCTIONS_SPREADSHEETCELL_HPP
