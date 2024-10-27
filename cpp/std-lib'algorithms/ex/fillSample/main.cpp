#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

static const size_t vecSize = 10;
static const int fillValue = 3;

void println(const auto &seq)
{
   for (const auto &item: seq)
   {
      std::cout << item << ' ';
   }

   std::cout << '\n';
}

int main()
{
   // using ranges::fill
   vector<int> vec(vecSize, {});
   ranges::fill(vec, fillValue);
   println(vec);

   // using std::fill()
   std::fill(vec.begin(), vec.end(), 7);
   println(vec);

   return 0;
}
