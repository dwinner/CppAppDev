#ifndef CPP20_OPERATORSDEFAULTED_SPREADSHEETCELL_HPP
#define CPP20_OPERATORSDEFAULTED_SPREADSHEETCELL_HPP


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

   SpreadsheetCell &operator+=(const SpreadsheetCell &rhs);

   SpreadsheetCell &operator-=(const SpreadsheetCell &rhs);

   SpreadsheetCell &operator*=(const SpreadsheetCell &rhs);

   SpreadsheetCell &operator/=(const SpreadsheetCell &rhs);

   [[nodiscard]] auto operator<=>(const SpreadsheetCell & /*rhs*/) const = default;

private:
   static std::string doubleToString(double value);

   static double stringToDouble(std::string_view value);

   double _value{0};
};

SpreadsheetCell operator+(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

SpreadsheetCell operator-(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

SpreadsheetCell operator*(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

SpreadsheetCell operator/(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);


#endif //CPP20_OPERATORSDEFAULTED_SPREADSHEETCELL_HPP
