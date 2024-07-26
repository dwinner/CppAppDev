#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
   SpreadsheetCell myCell1{4};
   SpreadsheetCell myCell2{myCell1};
   // myCell2 has the same values as myCell1

   cout << format("Cell 1: {}", myCell1.getValue()) << std::endl;
   cout << format("Cell 2: {}", myCell2.getValue()) << std::endl;

   return 0;
}
