#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
   SpreadsheetCell myCell, anotherCell;
   myCell.setValue(6);
   anotherCell.setString("3.2");

   cout << std::format("cell 1: {}", myCell.getValue()) << endl;
   cout << std::format("cell 2: {}", anotherCell.getValue()) << endl;

   return 0;
}
