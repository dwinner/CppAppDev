#include <iostream>

// An immediate function.
consteval int f(int i)
{
   return i;
}

// A constexpr function.
constexpr int g(int i)
{
   if consteval
   {
      return f(i);
   }
   else
   {
      return 42;
   }
}

//constexpr double inchToMm(double inch) { return inch * 25.4; }
consteval double inchToMm(double inch)
{
   return inch * 25.4;
}

int main()
{
   g(21);

   constexpr double const_inch{6.0};
   constexpr double mm1{inchToMm(const_inch)};    // at compile time

   double dynamic_inch{8.0};
   //double mm2{ inchToMm(dynamic_inch) };  // compile-time error
   return 0;
}
