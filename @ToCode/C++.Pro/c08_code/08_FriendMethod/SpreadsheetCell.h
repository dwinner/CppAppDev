#pragma once

#include <string>
#include "Spreadsheet.h"

class SpreadsheetCell
{
public:
	friend void Spreadsheet::setCellAt(int x, int y, const SpreadsheetCell& cell);

	SpreadsheetCell();
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(const std::string& initialValue);
	SpreadsheetCell(const SpreadsheetCell &src);

	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	void setValue(double inValue);
	double getValue() const;

	void setString(const std::string& inString);
	const std::string& getString() const;

private:
	std::string doubleToString(double inValue) const;
	double stringToDouble(const std::string& inString) const;

	double mValue;
	std::string mString;
};
