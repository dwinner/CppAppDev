#ifndef DESTRUCTORSFREESTORE_SPREADSHEETCELL_HPP
#define DESTRUCTORSFREESTORE_SPREADSHEETCELL_HPP

#include <string_view>

class SpreadsheetCell
{
public:
   SpreadsheetCell() = default;

   SpreadsheetCell(double initialValue);

   SpreadsheetCell(std::string_view initialValue);

   SpreadsheetCell(const SpreadsheetCell &src);

   // Destructor.
   ~SpreadsheetCell();

   void setValue(double value);

   double getValue() const;

   void setString(std::string_view value);

   std::string getString() const;

private:
   std::string doubleToString(double value) const;

   double stringToDouble(std::string_view value) const;

   double _value{0};
};


#endif //DESTRUCTORSFREESTORE_SPREADSHEETCELL_HPP
