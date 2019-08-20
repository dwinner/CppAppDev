#include <iostream>
#include <sstream>
#include <limits>

#include "DoubleSpreadsheetCell.h"

using namespace std;

DoubleSpreadsheetCell::DoubleSpreadsheetCell()
: mValue(std::numeric_limits<double>::quiet_NaN())
{
}

void DoubleSpreadsheetCell::set(double inDouble)
{
	mValue = inDouble;
}

void DoubleSpreadsheetCell::set(const string& inString)
{
	mValue = stringToDouble(inString);
}

string DoubleSpreadsheetCell::getString() const
{
	return doubleToString(mValue);
}

string DoubleSpreadsheetCell::doubleToString(double inValue)
{
	ostringstream ostr;

	ostr << inValue;
	return ostr.str();
}

double DoubleSpreadsheetCell::stringToDouble(const string& inValue)
{
	double temp;

	istringstream istr(inValue);

	istr >> temp;
	if (istr.fail() || !istr.eof()) {
		return 0;
	}
	return temp;
}
