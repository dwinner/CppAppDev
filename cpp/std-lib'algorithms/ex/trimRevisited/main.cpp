#include <ranges>
#include <print>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
   string sampleStr = "   sample  ";

   println("Before: '{}'", sampleStr);

   // interesting approach for function-style filtering,
   // but it doesn't work with strings
   ranges::for_each(
       sampleStr |
       views::drop_while([](char chr)
                         {
                            return std::isspace(chr);
                         }) |
       views::take_while([](char chr)
                         {
                            return !std::isspace(chr);
                         }),
       [](char chr)
       {
          return chr;
       }
   );

   println("After:  '{}'", sampleStr);
}
