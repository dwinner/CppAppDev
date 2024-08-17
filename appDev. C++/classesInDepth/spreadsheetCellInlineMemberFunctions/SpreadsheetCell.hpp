#ifndef SPREADSHEETCELLINLINEMEMBERFUNCTIONS_SPREADSHEETCELL_HPP
#define SPREADSHEETCELLINLINEMEMBERFUNCTIONS_SPREADSHEETCELL_HPP

#include <string_view>

class SpreadsheetCell
{
public:
   SpreadsheetCell() = default;

   SpreadsheetCell(double initialValue);

   SpreadsheetCell(std::string_view initialValue);

   void set(double value);

   void set(std::string_view value);

   inline double getValue() const
   {
      ++_numAccesses;
      return _value;
   }

   inline std::string getString() const
   {
      ++_numAccesses;
      return doubleToString(_value);
   }

private:
   static std::string doubleToString(double value);

   static double stringToDouble(std::string_view value);

   double _value{0};
   mutable unsigned _numAccesses{0};
};


#endif //SPREADSHEETCELLINLINEMEMBERFUNCTIONS_SPREADSHEETCELL_HPP
