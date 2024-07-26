#include <iostream>
#include <format>
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
   SpreadsheetCell myCell{"6.2"};
   cout << format("cell 1: {}", myCell.getValue()) << endl;

   return 0;
}
