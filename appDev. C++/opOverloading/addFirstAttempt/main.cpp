#include <iostream>
#include <print>
#include "SpreadsheetCell.hpp"

using namespace std;

int main()
{
   SpreadsheetCell myCell{4}, anotherCell{5};
   SpreadsheetCell aThirdCell{myCell.add(anotherCell)};
   auto aFourthCell{aThirdCell.add(anotherCell)};
   println("{}", aThirdCell.getValue());

   return 0;
}
