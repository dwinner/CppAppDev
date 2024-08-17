#include <iostream>
#include <format>
#include "SpreadsheetCell.hpp"

using namespace std;

int main()
{
   SpreadsheetCell myCell{5};
   cout << format("{}", myCell.getValue());
   return 0;
}
