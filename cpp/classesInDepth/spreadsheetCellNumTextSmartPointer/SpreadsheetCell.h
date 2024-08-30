#ifndef SPREADSHEETCELLNUMTEXTSMARTPOINTER_SPREADSHEETCELL_H
#define SPREADSHEETCELLNUMTEXTSMARTPOINTER_SPREADSHEETCELL_H

#include <string_view>

class SpreadsheetCell
{
public:
   void setValue(double value);

   double getValue() const;

   void setString(std::string_view value);

   std::string getString() const;

private:
   std::string doubleToString(double value) const;

   double stringToDouble(std::string_view value) const;

   double _value{0};
};

#endif //SPREADSHEETCELLNUMTEXTSMARTPOINTER_SPREADSHEETCELL_H
