#pragma once

#include "SpreadsheetCell.h"
#include "DoubleSpreadsheetCell.h"

class StringSpreadsheetCell : public SpreadsheetCell
{
public:
	StringSpreadsheetCell();
	StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell);

	virtual void set(const std::string& inString) override;

	virtual std::string getString() const override;

private:
	std::string mValue;
};
