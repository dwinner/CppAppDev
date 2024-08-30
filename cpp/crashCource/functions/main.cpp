#include <iostream>
#include <format>

using namespace std;

auto myFunction(int i, char c) -> void;

void myFunction(int i, char c)
{
   cout << format("The value of i is {}.", i) << endl;
   cout << format("The value of c is {}.", c) << endl;
}

int addNumbers(int number1, int number2)
{
   cout << format("Entering function {}", __func__);
   return number1 + number2;
}

// With function return type deduction
auto addNumbers(double a, double b)
{
   return a + b;
}

int main()
{
   int someInt{6};
   char someChar{'c'};
   myFunction(8, 'a');
   myFunction(someInt, 'b');
   myFunction(5, someChar);

   int sum{addNumbers(5, 3)};

   cout << format("{}", addNumbers(1, 2)) << endl;// Calls the integer version
   cout << format("{}", addNumbers(1.11, 2.22)) << endl;// Calls the double version

   return 0;
}
