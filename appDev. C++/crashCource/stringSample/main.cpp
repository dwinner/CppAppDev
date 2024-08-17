#include <iostream>
#include <format>

using namespace std;

int main()
{
   string myString{"Hi, C++ 23"};
   std::cout << std::format("The value of myString is {}", myString) << endl;
   std::cout << std::format("The second letter is {}", myString[1]) << endl;

   return 0;
}
