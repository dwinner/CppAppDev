#include <stdexcept>
#include <string>
#include <charconv>
#include "SpreadsheetCell.hpp"

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
    : _value{initialValue}
{
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
    : _value{stringToDouble(initialValue)}
{
}

void SpreadsheetCell::set(double value)
{
   _value = value;
}

double SpreadsheetCell::getValue() const
{
   return _value;
}

void SpreadsheetCell::set(string_view value)
{
   _value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
   return doubleToString(_value);
}

string SpreadsheetCell::doubleToString(double value)
{
   return to_string(value);
}

double SpreadsheetCell::stringToDouble(string_view value)
{
   double number{0};
   from_chars(value.data(), value.data() + value.size(), number);
   return number;
}

SpreadsheetCell operator+(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs)
{
   auto result{lhs};  // Local copy
   result += rhs;       // Forward to +=()
   return result;
}

SpreadsheetCell operator-(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs)
{
   auto result{lhs};  // Local copy
   result -= rhs;       // Forward to -=()
   return result;
}

SpreadsheetCell operator*(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs)
{
   auto result{lhs};  // Local copy
   result *= rhs;       // Forward to *=()
   return result;
}

SpreadsheetCell operator/(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs)
{
   auto result{lhs};  // Local copy
   result /= rhs;       // Forward to /=()
   return result;
}

SpreadsheetCell &SpreadsheetCell::operator+=(const SpreadsheetCell &rhs)
{
   set(getValue() + rhs.getValue());
   return *this;
}

SpreadsheetCell &SpreadsheetCell::operator-=(const SpreadsheetCell &rhs)
{
   set(getValue() - rhs.getValue());
   return *this;
}

SpreadsheetCell &SpreadsheetCell::operator*=(const SpreadsheetCell &rhs)
{
   set(getValue() * rhs.getValue());
   return *this;
}

SpreadsheetCell &SpreadsheetCell::operator/=(const SpreadsheetCell &rhs)
{
   if (rhs.getValue() == 0)
   {
      throw invalid_argument{"Divide by zero."};
   }

   set(getValue() / rhs.getValue());
   return *this;
}
