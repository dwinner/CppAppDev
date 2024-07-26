#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
   SpreadsheetCell myCell{4};
   myCell = 5;

   string_view sv = "6";
   myCell = (SpreadsheetCell) sv;

   // A string_view literal.
   myCell = (SpreadsheetCell) "6"sv;

   cout << format("Cell: {}", myCell.getValue()) << endl;

   return 0;
}
