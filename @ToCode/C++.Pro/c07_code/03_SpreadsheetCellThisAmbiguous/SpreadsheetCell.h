#pragma once

#include <string>

class SpreadsheetCell
{
public:
	void setValue(double value);
	double getValue() const;

	void setString(const std::string& inString);
	const std::string& getString() const;

private:
	std::string doubleToString(double inValue) const;
	double stringToDouble(const std::string& inString) const;

	double value;
	std::string mString;
};
