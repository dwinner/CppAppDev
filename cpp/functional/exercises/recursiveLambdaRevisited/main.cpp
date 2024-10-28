/*
Write a recursive lambda expression to calculate the power of a number. For
example, 4 to the power 3, written as 4^3, equals 4×4×4. Make sure it works with negative
exponents. To help you, 4^-3 equals 1/(4^3). Any number to the power 0 equals 1. Test your
lambda expression by generating all powers of two with exponents between -10 and 10.
 */

#include <ranges>
#include <print>

using namespace std;

int main()
{
   auto power{
       [](this auto &self, double value, int exponent)
       {
          if (exponent == 0)
          {
             return 1.0;
          }
          else if (exponent < 0)
          {
             return 1.0 / self(value, -exponent);
          }
          else
          {
             return value * self(value, exponent - 1);
          }
       }
   };

   auto values{views::iota(-10) | views::take(21)};
   for (const auto &item: values)
   {
      println("pow(2, {}) is {} ", item, power(2, item));
   }
}
