#include <iostream>
#include "SpreadsheetCell.hpp"

int main()
{
   SpreadsheetCell myCell, anotherCell, aThirdCell;

   myCell = anotherCell = aThirdCell;
   myCell.operator=(anotherCell.operator=(aThirdCell));

   SpreadsheetCell cell{4};
   cell = cell; // self-assignment

   return 0;
}
