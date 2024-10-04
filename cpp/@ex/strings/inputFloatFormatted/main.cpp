#include <iostream>
#include <print>
#include <vector>

using namespace std;

int main()
{
   println("Input float numbers until 0 is hit");

   vector<float> floatNumbers;
   float currentInput;
   cin >> currentInput;
   while (currentInput != 0)
   {
      floatNumbers.emplace_back(currentInput);
      cin >> currentInput;
   }

   constexpr int width = 6;
   constexpr int precision = 3;
   for (const auto &item: floatNumbers)
   {
      print("|{2:{0}.{1}f}| ", width, precision, item);
   }

   println();

   return 0;
}
