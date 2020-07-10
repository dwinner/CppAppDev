#include "SpreadsheetCell.h"

#include <iostream>
#include <sstream>
using namespace std;

void printCell(const SpreadsheetCell& inCell)
{
	cout << inCell.getString() << endl;
}

void SpreadsheetCell::setValue(double value)
{
	this->value = value;
	mString = doubleToString(this->value);
	printCell(*this);
}

double SpreadsheetCell::getValue() const
{
	return value;
}

void SpreadsheetCell::setString(const string& inString)
{
	mString = inString;
	value = stringToDouble(mString);
}

const string& SpreadsheetCell::getString() const
{
	return mString;
}

string SpreadsheetCell::doubleToString(double inValue) const
{
	ostringstream ostr;

	ostr << inValue;
	return ostr.str();
}

double SpreadsheetCell::stringToDouble(const string& inString) const
{
	double temp;

	istringstream istr(inString);

	istr >> temp;
	if (istr.fail() || !istr.eof()) {
		return 0;
	}
	return temp;
}
