#pragma once
#include <string>
using std::string;

class SpreadsheetCell
{
public:
	SpreadsheetCell();
	explicit SpreadsheetCell(double initialValue);
	explicit SpreadsheetCell(const string& initialValue);
	SpreadsheetCell(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
	void setValue(double inValue);
	double getValue() const;
	void setString(const string& inString);
	string getString() const;

protected:
	static string doubleToString(double inValue);
	static double stringToDouble(const string& inString);

	double mValue;
	string mString;
};
