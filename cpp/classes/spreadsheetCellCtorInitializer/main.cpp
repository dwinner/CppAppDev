#include <iostream>
#include <memory>
#include <format>
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
   SpreadsheetCell myCell;
   myCell.setValue(6);
   cout << format("cell 1: {}", myCell.getValue()) << endl;

   auto smartCellp{make_unique<SpreadsheetCell>()};
   // Or with a raw pointer (not recommended)
   SpreadsheetCell *myCellp{new SpreadsheetCell{}};
   // Or
   // SpreadsheetCell* myCellp{ new SpreadsheetCell };
   // ... use myCellp
   delete myCellp;
   myCellp = nullptr;

   return 0;
}
