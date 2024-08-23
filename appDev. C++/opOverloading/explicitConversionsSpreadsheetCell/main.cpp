#include <print>
#include "SpreadsheetCell.hpp"

using namespace std;

int main()
{
   SpreadsheetCell cell{6.6};

   double d1{cell + 3.4};
   println("{}", d1);

   return 0;
}
