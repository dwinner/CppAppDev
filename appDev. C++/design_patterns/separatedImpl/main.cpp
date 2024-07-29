/**
 * Bridge like implementation for separated instance
 */

#include <iostream>
#include "Spreadsheet.hpp"

using namespace std;

int main()
{
   Spreadsheet s1{};
   Spreadsheet s2{5, 6};
   Spreadsheet s3{s2};
   s1 = s3;
   s1 = std::move(s3);

   cout << s1.getId() << endl;
   cout << s2.getId() << endl;

   // s3 is moved and lost its ownership, so access violation would occur
   // cout << s3.getId() << endl;

   return 0;
}
