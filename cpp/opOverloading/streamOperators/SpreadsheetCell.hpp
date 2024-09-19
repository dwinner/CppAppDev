#ifndef STREAMOPERATORS_SPREADSHEETCELL_HPP
#define STREAMOPERATORS_SPREADSHEETCELL_HPP


#include <istream>

class SpreadsheetCell
{
public:
   SpreadsheetCell() = default;

   SpreadsheetCell(double initialValue);

   explicit SpreadsheetCell(std::string_view initialValue);

   void set(double value);

   void set(std::string_view value);

   inline double getValue() const
   {
      return value_;
   }

   inline std::string getString() const
   {
      return doubleToString(value_);
   }

   static std::string doubleToString(double value);

   static double stringToDouble(std::string_view value);

   SpreadsheetCell &operator+=(const SpreadsheetCell &rhs);

   SpreadsheetCell &operator-=(const SpreadsheetCell &rhs);

   SpreadsheetCell &operator*=(const SpreadsheetCell &rhs);

   SpreadsheetCell &operator/=(const SpreadsheetCell &rhs);

   [[nodiscard]] auto operator<=>(const SpreadsheetCell &) const = default;

   SpreadsheetCell operator-() const;

   SpreadsheetCell &operator++();   // prefix

   SpreadsheetCell operator++(int); // postfix

   SpreadsheetCell &operator--();   // prefix

   SpreadsheetCell operator--(int); // postfix

private:
   double value_{0};
};

SpreadsheetCell operator+(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

SpreadsheetCell operator-(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

SpreadsheetCell operator*(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

SpreadsheetCell operator/(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);

std::ostream &operator<<(std::ostream &ostream, const SpreadsheetCell &cell);

std::istream &operator>>(std::istream &istream, SpreadsheetCell &cell);


#endif //STREAMOPERATORS_SPREADSHEETCELL_HPP