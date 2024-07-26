#include <charconv>
#include <string>
#include "SpreadsheetCell.h"

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
    : _value{initialValue}
{
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
    : _value{stringToDouble(initialValue)}
{
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell &src)
    : _value{src._value}
{
}

void SpreadsheetCell::setValue(double value)
{
   _value = value;
}

double SpreadsheetCell::getValue() const
{
   return _value;
}

void SpreadsheetCell::setString(string_view value)
{
   _value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
   return doubleToString(_value);
}

string SpreadsheetCell::doubleToString(double value) const
{
   return to_string(value);
}

double SpreadsheetCell::stringToDouble(string_view value) const
{
   double number{0};
   from_chars(value.data(), value.data() + value.size(), number);
   return number;
}
