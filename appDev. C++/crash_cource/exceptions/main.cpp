#include <stdexcept>
#include <iostream>
#include <format>

using namespace std;

double divideNumbers(double numerator, double denominator)
{
   if (denominator == 0)
   {
      throw invalid_argument{"Denominator cannot be 0."};
   }

   return numerator / denominator;
}

int main()
{
   try
   {
      cout << std::format("{}", divideNumbers(2.5, 0.5)) << endl;
      cout << std::format("{}", divideNumbers(2.3, 0)) << endl;
      cout << std::format("{}", divideNumbers(4.5, 2.5)) << endl;
   }
   catch (const std::invalid_argument &exception)
   {
      cout << std::format("Exception caught: {}", exception.what()) << endl;
   }
}
