#include <vector>
#include <print>
#include <algorithm>

using namespace std;

int main()
{
   vector<int> values(10); // Create a vector of 10 elements.
   int value{1};
   generate(begin(values), end(values), [&value]
   {
      value *= 2;
      return value;
   });
   for (const auto &item: values)
   {
      println("{}", item);
   }
}
