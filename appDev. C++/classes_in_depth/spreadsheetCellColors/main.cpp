#include <iostream>
#include "SpreadsheetCell.hpp"

int main()
{
   SpreadsheetCell myCell{5};
   myCell.setColor(SpreadsheetCell::Color::Blue);
   auto color{myCell.getColor()};

   return 0;
}
