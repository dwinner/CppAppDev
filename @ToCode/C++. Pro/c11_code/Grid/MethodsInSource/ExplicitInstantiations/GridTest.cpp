#include "Grid.h"

#include <vector>
using namespace std;

void processIntGrid(Grid<int>& /*inGrid*/)
{
	// body omitted for brevity
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

	processIntGrid(myIntGrid);

	Grid<vector<int>> gridOfVectors;
	vector<int> myVector{ 1, 2, 3, 4 };
	gridOfVectors.setElementAt(5, 6, myVector);

	return 0;
}
