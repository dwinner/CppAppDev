#ifndef SPREADSHEETCELLEXPLICITOBJECTPARAMETER_SPREADSHEETCELL_H
#define SPREADSHEETCELLEXPLICITOBJECTPARAMETER_SPREADSHEETCELL_H

#include <string_view>

class SpreadsheetCell
{
public:
   void setValue(this SpreadsheetCell &self, double value);

   double getValue() const;

   void setString(std::string_view value);

   std::string getString() const;

private:
   std::string doubleToString(double value) const;

   double stringToDouble(std::string_view value) const;

   double _value{0};
};


#endif //SPREADSHEETCELLEXPLICITOBJECTPARAMETER_SPREADSHEETCELL_H
