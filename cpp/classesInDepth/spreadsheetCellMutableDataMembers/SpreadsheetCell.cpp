#include <charconv>
#include <string>
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

void SpreadsheetCell::setValue(double value)
{
   _value = value;
}

double SpreadsheetCell::getValue() const
{
   ++_numAccesses;
   return _value;
}

void SpreadsheetCell::setString(string_view value)
{
   _value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
   ++_numAccesses;
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