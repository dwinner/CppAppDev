#ifndef SPREADSHEETCELLMUTABLEDATAMEMBERS_SPREADSHEETCELL_HPP
#define SPREADSHEETCELLMUTABLEDATAMEMBERS_SPREADSHEETCELL_HPP


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
   mutable unsigned _numAccesses{0};
};


#endif //SPREADSHEETCELLMUTABLEDATAMEMBERS_SPREADSHEETCELL_HPP
