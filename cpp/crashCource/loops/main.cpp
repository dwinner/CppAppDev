#include <iostream>
#include <format>

using namespace std;

int main()
{
   {
      // The while loop
      int i{0};
      while (i < 5)
      {
         cout << "This is silly." << endl;
         ++i;
      }
   }

   cout << endl;

   {
      // The do/while loop
      int i{100};
      do
      {
         cout << "This is silly." << endl;
         ++i;
      }
      while (i < 5);
   }

   cout << endl;

   {
      // The for loop
      for (int i{0}; i < 5; ++i)
      {
         cout << "This is silly." << endl;
      }
   }

   cout << endl;

   {
      // The range-based for loop
      array arr{1, 2, 3, 4};
      for (int i: arr)
      {
         std::cout << std::format("{}", i) << std::endl;
      }
   }

   cout << endl;

   {
      // The range-based for loop with initializer
      for (array arr{1, 2, 3, 4}; int i : arr) {
         std::cout << std::format("{}", i) << std::endl;
      }
   }

   return 0;
}
