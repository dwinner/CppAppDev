/**
 * modulus.cpp -- uses % operator to convert lbs to stone
 */

#include <iostream>

int main()
{
   using namespace std;
   const auto lbs_per_stn = 14;
   int lbs;

   cout << "Enter your weight in pounds: ";
   cin >> lbs;
   int stone = lbs / lbs_per_stn; // whole stone
   int pounds = lbs % lbs_per_stn; // remainder in pounds
   cout << lbs << " pounds are " << stone
      << " stone, " << pounds << " pound(s).\n";

   cin.get();
   cin.get();

   return 0;
}
