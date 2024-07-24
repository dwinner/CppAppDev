#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

int main()
{
   SpreadsheetCell *myCellp{new SpreadsheetCell{}};

   myCellp->setValue(3.7);
   std::cout << std::format("cell 1: {} {}",
                            myCellp->getValue(),
                            myCellp->getString()) << std::endl;
   delete myCellp;
   myCellp = nullptr;

   return 0;
}
