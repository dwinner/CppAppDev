#pragma once

#include "SpreadsheetCell.h"

class DoubleSpreadsheetCell : public SpreadsheetCell
{
public:
	DoubleSpreadsheetCell();
	virtual void set(double inDouble);
	virtual void set(const std::string& inString) override;

	virtual std::string getString() const override;

private:
	static std::string doubleToString(double inValue);
	static double stringToDouble(const std::string& inValue);

	double mValue;
};
