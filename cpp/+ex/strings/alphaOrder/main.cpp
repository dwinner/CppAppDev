#include <iostream>
#include <print>
#include <string>

using namespace std;

int main()
{
   string str1;
   string str2;

   println("Enter the 1St string: ");
   getline(cin, str1);

   println("Enter the 2Nd string: ");
   getline(cin, str2);

   strong_ordering spaceShipResult = str1 <=> str2;
   if (spaceShipResult == strong_ordering::less)
   {
      println("Alphabetical order: {} {}", str1, str2);
   }
   else if (spaceShipResult == strong_ordering::greater)
   {
      println("Alphabetical order: {} {}", str2, str1);
   }
   else
   {
      println("Strings are the same");
   }

   return 0;
}
