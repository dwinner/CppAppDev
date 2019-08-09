#include "SpreadsheetCell.h"
#include <iostream>
using namespace std;

int main()
{
	SpreadsheetCell myCell(123);

	//double (SpreadsheetCell::*methodPtr) () const = &SpreadsheetCell::getValue;

	//using PtrToGet = double (SpreadsheetCell::*) () const;	// equivalent to: typedef double (SpreadsheetCell::*PtrToGet) () const;
	//PtrToGet methodPtr = &SpreadsheetCell::getValue;

	auto methodPtr = &SpreadsheetCell::getValue;

	cout << (myCell.*methodPtr)() << endl;

	return 0;
}
