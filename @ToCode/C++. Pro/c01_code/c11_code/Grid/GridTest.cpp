#include "Grid.h"
#include "SpreadsheetCell.h"

#include <vector>
#include <memory>
using namespace std;

void processIntGrid(Grid<int>& /*inGrid*/)
{
	// Body omitted for brevity
}

int main()
{
	Grid<int> myIntGrid; // declares a grid that stores ints, using default parameters for the constructor
	Grid<double> myDoubleGrid(11, 11); // declares an 11x11 Grid of doubles
	myIntGrid.setElementAt(0, 0, 10);
	int x = myIntGrid.getElementAt(0, 0);

	Grid<int> grid2(myIntGrid);  // Copy constructor
	Grid<int> anotherIntGrid;
	anotherIntGrid = grid2;      // Assignment operator

	//Grid test;   // WILL NOT COMPILE
	//Grid<> test; // WILL NOT COMPILE

	processIntGrid(myIntGrid);

	Grid<SpreadsheetCell> mySpreadsheet;
	SpreadsheetCell myCell("Test");
	mySpreadsheet.setElementAt(3, 4, myCell);

	Grid<const char*> myStringGrid;
	myStringGrid.setElementAt(2, 2, "hello");

	Grid<vector<int>> gridOfVectors;
	vector<int> myVector{ 1, 2, 3, 4 };
	gridOfVectors.setElementAt(5, 6, myVector);

	auto myGridp = make_unique<Grid<int>>(2, 2); // creates a 2x2 Grid on the heap
	myGridp->setElementAt(0, 0, 10);
	x = myGridp->getElementAt(0, 0);

	return 0;
}
