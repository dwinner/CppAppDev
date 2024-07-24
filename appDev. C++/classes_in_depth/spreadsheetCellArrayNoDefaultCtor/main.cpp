#include <iostream>
#include "SpreadsheetCell.h"

int main()
{
   // Comment out these next two lines to test the third line
   // FAILS compilation without a default constructor
   //SpreadsheetCell cells[3];

   // also FAILS
   //SpreadsheetCell *myCellp{new SpreadsheetCell[10]};

   // This line compiles without a default constructor
   SpreadsheetCell cells[3]
       {
           SpreadsheetCell{0},
           SpreadsheetCell{23},
           SpreadsheetCell{41}
       };

   for (const auto &item: cells)
   {
      std::cout << item.getValue() << std::endl;
   }

   return 0;
}
