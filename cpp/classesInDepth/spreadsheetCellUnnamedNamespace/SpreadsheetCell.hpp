#ifndef SPREADSHEETCELLUNNAMEDNAMESPACE_SPREADSHEETCELL_HPP
#define SPREADSHEETCELLUNNAMEDNAMESPACE_SPREADSHEETCELL_HPP

#include <string>

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
   double _value{0};
};


#endif //SPREADSHEETCELLUNNAMEDNAMESPACE_SPREADSHEETCELL_HPP
