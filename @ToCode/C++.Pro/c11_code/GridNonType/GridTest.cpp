#include "Grid.h"

#include <iostream>
using namespace std;

constexpr size_t getHeight()
{
	return 10;
}

int main()
{
	Grid<int, 10, 10> myGrid;
	Grid<int, 10, 10> anotherGrid;

	myGrid.setElementAt(2, 3, 45);
	anotherGrid = myGrid;

	cout << anotherGrid.getElementAt(2, 3);

	Grid<double, 2, getHeight()> myDoubleGrid;

	return 0;
}
