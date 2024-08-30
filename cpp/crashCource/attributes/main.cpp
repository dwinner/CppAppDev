#include <iostream>
#include <format>

using namespace std;

int divideBy32(int x)
{
   [[assume(x >= 0)]];
   return x / 32;
}

void likeliHood()
{
   int value{4};
   if (value > 11) [[unlikely]]
   {
      /* Do something ... */
   }
   else
   {
      /* Do something else... */
   }

   switch (value)
   {
      [[likely]] case 1:
         // Do something ...
         break;
      case 2:
         // Do something...
         break;
         [[unlikely]] case 12:
         // Do something...
         break;
   }
}

[[deprecated("Unsafe function, please use xyz")]] void func()
{}

[[noreturn]] void forceProgramTermination()
{
   exit(1);  // Defined in <cstdlib>
}

bool isDongleAvailable()
{
   bool isAvailable{false};
   // Check whether a licensing dongle is available...
   return isAvailable;
}

bool isFeatureLicensed(int featureId)
{
   if (!isDongleAvailable())
   {
      // No licensing dongle found, abort program execution!
      forceProgramTermination();
   }
   else
   {
      // Dongle available, perform license check of the given feature...
      bool isLicensed{featureId == 42};
      return isLicensed;
   }
}

int func(int param1, [[maybe_unused]] int param2)
{
   return 42;
}


[[nodiscard]] int func2()
{
   return 42;
}

int main()
{
   cout << format("Result: {}", divideBy32(64)) << endl;
   likeliHood();
   func();

   bool isLicensed{isFeatureLicensed(42)};
   cout << format("{}", isLicensed) << endl;

   int result{func(1, 2)};

   func2();

   return 0;
}
