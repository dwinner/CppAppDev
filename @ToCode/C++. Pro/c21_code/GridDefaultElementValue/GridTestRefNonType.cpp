#include "GridRefNonType.h"
#include "SpreadsheetCell.h"

namespace {
	const int defaultInt = 11;
	const SpreadsheetCell defaultCell(1.2);
	// NOTE:
	//		Using the above definitions does not work with Microsoft VC++ 2013.
	//		Use the following instead:
	// int defaultInt = 11;
	// SpreadsheetCell defaultCell(1.2);
}

int main()
{
	Grid<int, defaultInt> myIntGrid;
	Grid<SpreadsheetCell, defaultCell> mySpreadsheet;

	Grid<int, defaultInt> myIntGrid2(myIntGrid);

	return 0;
}
