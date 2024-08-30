#include <iostream>
#include <format>
#include "SpreadsheetCell.hpp"

using namespace std;

int main()
{
   SpreadsheetCell *cellPtr1{new SpreadsheetCell{5}};
   SpreadsheetCell *cellPtr2{new SpreadsheetCell{6}};

   cout << format("cellPtr1: {}", cellPtr1->getValue()) << endl;

   delete cellPtr1; // destroys cellPtr1
   cellPtr1 = nullptr;

   return 0;
}
