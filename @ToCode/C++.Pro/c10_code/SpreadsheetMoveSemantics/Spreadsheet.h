#pragma once

#include "SpreadsheetCell.h"

class Spreadsheet
{
public:
	Spreadsheet(int inWidth, int inHeight);
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet(Spreadsheet&& src) noexcept; // Move constructor
	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhs);
	Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;  // Move assignment

	void setCellAt(int x, int y, const SpreadsheetCell& cell);
	SpreadsheetCell getCellAt(int x, int y);

private:
	bool inRange(int val, int upper);
	void copyFrom(const Spreadsheet& src);
	void freeMemory();

	int mWidth, mHeight;
	SpreadsheetCell** mCells;
};
