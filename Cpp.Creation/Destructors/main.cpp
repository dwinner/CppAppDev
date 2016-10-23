#include <iostream>
#include "SpreadsheetCell.h"

using namespace std;

void heapExample(void);

void detorExample(void);

int main()
{
   heapExample();
   detorExample();

   return 0;
}

void heapExample(void)
{
   SpreadsheetCell *cellPtr1 = new SpreadsheetCell(5);
   SpreadsheetCell *cellPtr2 = new SpreadsheetCell(6);

   cout << "cellPtr1: " << cellPtr1->getValue() << endl;

   delete cellPtr1;  // destoys cellPtr1
   cellPtr1 = nullptr;

   // NOTE: cellPtr2 is NOT destroyed because delete was not called on it
}

void detorExample(void)
{
   SpreadsheetCell myCell(5);

   if (myCell.getValue() == 5)
   {
      SpreadsheetCell anotherCell(6);
   }  // anotherCell is destroyed as this block ends

   cout << "myCell: " << myCell.getValue() << endl;

   {
      SpreadsheetCell myCell2(4);
      SpreadsheetCell anotherCell2(5); // myCell2 constructed before anotherCell2
   }  // anotherCell2 destoyed before myCell2
}  // myCell is destroyed as this block ends
