#include <vector>
#include <functional>
#include <print>
#include "Processor.hpp"

using namespace std;

int main()
{
   vector<function<int(int)>> callbacks =
       {
           [](int val)
           { return val; },
           [](int val)
           { return val * 2; },
           [](int val)
           { return val * 3; },
           [](int val)
           { return val * 4; }
       };

   Processor processor{
       [](int val)
       { return val * val; }
   };
   auto result = processor(8);
   println("Default result: {}", result);

   for (const auto &item: callbacks)
   {
      processor.setDelegate(item);
      println("Current result: {}", processor(8));
   }
}
