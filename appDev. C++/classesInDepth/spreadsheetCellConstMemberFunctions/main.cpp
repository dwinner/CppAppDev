#include <iostream>
#include <format>
#include "SpreadsheetCell.hpp"

using namespace std;

int main()
{
   SpreadsheetCell myCell{5};
   cout << format("{}", myCell.getValue()) << endl;       // OK
   myCell.setString("6");                  // OK

   const SpreadsheetCell &myCellConstRef{myCell};
   cout << format("{}", myCellConstRef.getValue()) << endl; // OK
   //myCellConstRef.setString("6"); // Compilation Error!

   return 0;
}
