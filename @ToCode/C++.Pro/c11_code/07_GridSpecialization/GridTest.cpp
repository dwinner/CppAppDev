#include <iostream>
#include <string>
using namespace std;

#include "GridString.h"

int main()
{
	Grid<int> myIntGrid;					// Uses original Grid template
	Grid<const char*> stringGrid1(2, 2);	// Uses const char* specialization

	const char* dummy = "dummy";
	stringGrid1.setElementAt(0, 0, "hello");
	stringGrid1.setElementAt(0, 1, dummy);
	stringGrid1.setElementAt(1, 0, dummy);
	stringGrid1.setElementAt(1, 1, "there");

	Grid<const char*> stringGrid2(stringGrid1);

	cout << stringGrid1.getElementAt(0, 1) << endl;
	cout << stringGrid2.getElementAt(0, 1) << endl;

	return 0;
}
