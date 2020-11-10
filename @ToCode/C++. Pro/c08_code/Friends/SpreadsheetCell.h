#pragma once

#include <string>

class SpreadsheetCell
{
public:
	SpreadsheetCell();
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(const std::string& initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);

	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	void set(double inValue);
	void set(const std::string& inString);

	double getValue() const { mNumAccesses++; return mValue; }
	const std::string& getString() const { mNumAccesses++; return mString; }

	static std::string doubleToString(double inValue);
	static double stringToDouble(const std::string& inString);

	friend bool checkSpreadsheetCell(const SpreadsheetCell& cell);

private:
	double mValue;
	std::string mString;

	mutable int mNumAccesses = 0;
};
