// AssignerSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SpreadsheetCell.h"

int main()
{
	SpreadsheetCell myCell(5);
	auto anotherCell(myCell);
	auto aThirdCell = myCell;
	anotherCell = myCell; // Calls operator= for anotherCell

	SpreadsheetCell myCell2(5);
	string s1;
	s1 = myCell2.getString();

	SpreadsheetCell myCell3(5);
	auto s2 = myCell3.getString();

	SpreadsheetCell cell1, cell2, cell3;
	cell1 = cell2 = cell3;
	cell1.operator=(cell2.operator=(cell3));

	SpreadsheetCell cell4(4);
	cell4 = cell4; // Self-assignment

	return 0;
}
