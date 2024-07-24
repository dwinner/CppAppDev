#ifndef SPREADSHEETCELLCTORS_SPREADSHEETCELL_H
#define SPREADSHEETCELLCTORS_SPREADSHEETCELL_H

#include <string_view>

class SpreadsheetCell
{
public:
   SpreadsheetCell(double initialValue);

   SpreadsheetCell(std::string_view initialValue);

   void setValue(double value);

   double getValue() const;

   void setString(std::string_view value);

   std::string getString() const;

private:
   std::string doubleToString(double value) const;

   double stringToDouble(std::string_view value) const;

   double _value{0};
};


#endif //SPREADSHEETCELLCTORS_SPREADSHEETCELL_H
