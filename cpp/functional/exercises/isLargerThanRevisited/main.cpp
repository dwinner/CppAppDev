#include <span>
#include <print>
#include <vector>

using namespace std;

template<predicate<int, int> Matcher, invocable<size_t, int, int> MatchHandler>
void findMatches(span<const int> values1,
                 span<const int> values2,
                 Matcher matcher,
                 MatchHandler handler)
{
   // Must be same size.
   if (values1.size() != values2.size())
   {
      return;
   }

   for (size_t i{0}; i < values1.size(); ++i)
   {
      if (matcher(values1[i], values2[i]))
      {
         handler(i, values1[i], values2[i]);
      }
   }
}

int main()
{
   vector values1{2, 500, 6, 9, 10, 101, 1};
   vector values2{4, 4, 2, 9, 0, 300, 1};

   findMatches(
       values1,
       values2,
       [val = 100](int val1, int val2) -> bool
       {
          return val1 > val && val2 > val;
       },
       [](size_t position, int val1, int val2) -> void
       {
          println("Match found at position {} ({}, {})", position, val1, val2);
       });
}
