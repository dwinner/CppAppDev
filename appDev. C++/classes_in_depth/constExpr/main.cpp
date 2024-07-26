#include <iostream>

using namespace std;

constexpr int getArraySize()
{
   return 32;
}

void log(string_view message)
{
   cout << format("{}", message);
}

constexpr int computeSomething(bool someFlag)
{
   if (someFlag)
   {
      log("someFlag is true");
      return 42;
   }
   else
   {
      return 84;
   }
}

int main()
{
   {
      int myArray[getArraySize()];    // OK
      cout << format("Size of array = {}", size(myArray)) << endl;
   }

   {
      int myArray[getArraySize() + 1]; // OK
      cout << format("Size of array = {}", size(myArray)) << endl;
   }

   {
      constexpr auto value1{computeSomething(false)};
      //constexpr auto value2{ computeSomething(true) }; // Error: doesn't compile!
      const auto value3{computeSomething(true)};
   }

   return 0;
}
