#include <iostream>
#include <array>
#include <format>

using namespace std;

void stdArraySample()
{
   array<int, 3> arr{9, 8, 7};
   // array arr{ 9, 8, 7 };  // Using CTAD
   cout << std::format("Array size = {}", arr.size()) << endl;
   cout << std::format("2nd element = {}", arr[1]) << endl;
}

void cArray()
{
   {
      int myArray[3];
      myArray[0] = 0;
      myArray[1] = 0;
      myArray[2] = 0;
   }

   {
      int myArray[3] = {0};
   }

   {
      int myArray[3] = {};
   }

   {
      int myArray[3]{};
   }

   {
      int myArray[]{1, 2, 3, 4}; // The compiler creates an array of 4 elements.
   }

   {
      int myArray[3]{2};
      std::size_t arraySize1{std::size(myArray)};
      std::size_t arraySize2{sizeof(myArray) / sizeof(myArray[0])};
   }

   {
      char ticTacToeBoard[3][3];
      ticTacToeBoard[1][1] = 'o';
   }
}

int main()
{
   stdArraySample();
   cArray();

   return 0;
}
