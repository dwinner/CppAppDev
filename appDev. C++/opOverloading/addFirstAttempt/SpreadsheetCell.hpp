#ifndef ADDFIRSTATTEMPT_SPREADSHEETCELL_HPP
#define ADDFIRSTATTEMPT_SPREADSHEETCELL_HPP


#include <string>
#include <string_view>

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

   SpreadsheetCell add(const SpreadsheetCell &cell) const;

private:
   static std::string doubleToString(double value);

   static double stringToDouble(std::string_view value);

   double _value{0};
};


#endif //ADDFIRSTATTEMPT_SPREADSHEETCELL_HPP
