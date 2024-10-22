#include <print>
#include <span>
#include <vector>
#include <array>

using namespace std;

void printSpan(span<const int> values)
{
   for (const auto &value: values)
   {
      print("{} ", value);
   }

   println("");
}

int main()
{
   vector v{11, 22, 33, 44, 55, 66};

   // Pass the whole vector, implicitly converted to a span.
   printSpan(v);

   // Pass an explicitly created span.
   span mySpan{v};
   printSpan(mySpan);

   // Create a subview and pass that.
   span subSpan{mySpan.subspan(2, 3)};
   printSpan(subSpan);

   // Pass a subview created in-line.
   printSpan({v.data() + 2, 3});

   // Pass std::array.
   array<int, 5> arr{5, 4, 3, 2, 1};
   printSpan(arr);
   printSpan({arr.data() + 2, 3});

   // Pass a C-style array.
   int carr[]{9, 8, 7, 6, 5};
   printSpan(carr);            // The entire C-style array.
   printSpan({carr + 2, 3}); // A subview of the C-style array.
}
