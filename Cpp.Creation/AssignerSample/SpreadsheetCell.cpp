#include "stdafx.h"
#include "SpreadsheetCell.h"
#include <iostream>
#include <sstream>

using namespace std;

SpreadsheetCell::SpreadsheetCell()
	: mValue(0), mString("")
{
}

SpreadsheetCell::SpreadsheetCell(double initialValue)
{
	setValue(initialValue);
}

SpreadsheetCell::SpreadsheetCell(const string& initialValue)
	: mValue(stringToDouble(initialValue)), mString(initialValue)
{
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& rhs)
{
	mValue = rhs.mValue;
	mString = rhs.mString;
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	mValue = rhs.mValue;
	mString = rhs.mString;

	return *this;
}

void SpreadsheetCell::setValue(double inValue)
{
	mValue = inValue;
	mString = doubleToString(mValue);
}

double SpreadsheetCell::getValue() const
{
	return mValue;
}

void SpreadsheetCell::setString(const string& inString)
{
	mString = inString;
	mValue = stringToDouble(mString);
}

string SpreadsheetCell::getString() const
{
	return mString;
}

string SpreadsheetCell::doubleToString(double inValue)
{
	ostringstream ostr;
	ostr << inValue;

	return ostr.str();
}

double SpreadsheetCell::stringToDouble(const string& inString)
{
	double temp;
	istringstream istr(inString);
	istr >> temp;

	return istr.fail() || !istr.eof() ? 0 : temp;
}
