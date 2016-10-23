//
// Created by Denny on 10/23/2016.
//
#include <string>

using std::string;

#ifndef DESTRUCTORS_SPREADSHEETCELL_H
#define DESTRUCTORS_SPREADSHEETCELL_H

class SpreadsheetCell
{
public:
   SpreadsheetCell();

   SpreadsheetCell(double initialValue);

   SpreadsheetCell(const string initialValue);

   SpreadsheetCell(const SpreadsheetCell &src);

   void setValue(double inValue);

   double getValue() const;

   void setString(const string &inString);

   string getString() const;

protected:
   string doubleToString(double inValue) const;

   double stringToDouble(const string &inString) const;

   double mValue;
   string mString;
};

#endif //DESTRUCTORS_SPREADSHEETCELL_H
