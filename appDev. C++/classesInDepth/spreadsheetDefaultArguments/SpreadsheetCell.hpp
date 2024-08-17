#ifndef SPREADSHEETDEFAULTARGUMENTS_SPREADSHEETCELL_HPP
#define SPREADSHEETDEFAULTARGUMENTS_SPREADSHEETCELL_HPP

#include <string>

class SpreadsheetCell
{
public:
   SpreadsheetCell() = default;

   SpreadsheetCell(double initialValue);

   SpreadsheetCell(std::string_view initialValue);

   void set(double value);

   void set(std::string_view value);

   double getValue() const;

   std::string getString() const;

private:
   std::string doubleToString(double value) const;

   double stringToDouble(std::string_view value) const;

   double _value{0};
};


#endif //SPREADSHEETDEFAULTARGUMENTS_SPREADSHEETCELL_HPP
