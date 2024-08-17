#include <iostream>
#include <vector>
#include <format>
#include "Spreadsheet.hpp"

using namespace std;

Spreadsheet createObject()
{
   cout << "In " << __func__ << endl;
   return Spreadsheet{3, 2};
}

int main()
{
   vector<Spreadsheet> vec;
   for (size_t i{0}; i < 2; ++i)
   {
      cout << format("Iteration {}", i) << endl;
      vec.emplace_back(100, 100);
      cout << format("") << endl;
   }

   cout << "========================================" << endl;

   Spreadsheet s{2, 3};
   s = createObject();

   cout << format("------------------------------------") << endl;

   Spreadsheet s2{5, 6};
   s2 = s;

   return 0;
}
