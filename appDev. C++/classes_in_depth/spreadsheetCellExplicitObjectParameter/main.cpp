#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

int main()
{
   SpreadsheetCell myCell, anotherCell;
   myCell.setValue(6);
   anotherCell.setString("3.2");

   std::cout << std::format("cell 1: {}", myCell.getValue()) << std::endl;
   std::cout << std::format("cell 2: {}", anotherCell.getValue()) << std::endl;

   return 0;
}
