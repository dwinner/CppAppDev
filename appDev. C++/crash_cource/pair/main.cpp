#include <iostream>
#include <format>

using namespace std;

int main()
{
   pair<double, int> myPair{1.23, 5};
   // pair myPair { 1.23, 5 };  // Using CTAD
   cout << std::format("{} {}", myPair.first, myPair.second) << endl;

   return 0;
}
