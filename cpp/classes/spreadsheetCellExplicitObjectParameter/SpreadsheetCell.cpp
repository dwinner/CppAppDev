#include <string>
#include <charconv>
#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

using namespace std;

void printCell(const SpreadsheetCell &cell)
{
   std::cout << std::format("{}", cell.getString()) << std::endl;
}

void SpreadsheetCell::setValue(this SpreadsheetCell &self, double value)
{
   self._value = value;
   printCell(self);
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