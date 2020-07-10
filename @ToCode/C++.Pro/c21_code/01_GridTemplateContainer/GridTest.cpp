#include "Grid.h"

#include <vector>
#include <deque>
#include <iostream>
using namespace std;

int main()
{
	Grid<int, vector<int>> myIntVectorGrid;
	Grid<int, deque<int>> myIntDequeGrid;

	myIntVectorGrid.setElementAt(3, 4, 5);
	cout << myIntVectorGrid.getElementAt(3, 4) << endl;

	myIntDequeGrid.setElementAt(1, 2, 3);
	cout << myIntDequeGrid.getElementAt(1, 2) << endl;

	Grid<int, vector<int>> grid2(myIntVectorGrid);
	grid2 = myIntVectorGrid;

	//Grid<int, int> test; // WILL NOT COMPILE

	return 0;
}
