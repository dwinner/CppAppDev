#include <iostream>

#include "Stone.h"

using namespace stone_sample;
using std::cout;

void display(const Stone& aStone, int n);

int main()
{
   const Stone poppins(9, 2.8); // 9 stone, 2.8 pounds
   const double pWt = poppins; // implicit conversion
   cout << "Convert to double => ";
   cout << "Poppins: " << pWt << " pounds.\n";
   cout << "Convert to int => ";
   cout << "Poppins: " << static_cast<int>(poppins) << " pounds.\n";

   Stone incognito = 275; // uses constructor to initialize
   const Stone wolfe(285.7);    // same as Stonewt wolfe = 285.7;
   Stone taft(21, 8);

   cout << "The celebrity weighed ";
   incognito.show_stn();
   cout << "The detective weighed ";
   wolfe.show_stn();
   cout << "The President weighed ";
   taft.show_lbs();
   incognito = 276.8;      // uses constructor for conversion
   taft = 325;             // same as taft = Stonewt(325);
   cout << "After dinner, the celebrity weighed ";
   incognito.show_stn();
   cout << "After dinner, the President weighed ";
   taft.show_lbs();
   display(taft, 2);
   cout << "The wrestler weighed even more.\n";
   display(422, 2);
   cout << "No stone left unearned\n";

   return 0;
}

void display(const Stone& aStone, const int n)
{
   for (int i = 0; i < n; i++)
   {
      cout << "Wow! ";
      aStone.show_stn();
   }
}
