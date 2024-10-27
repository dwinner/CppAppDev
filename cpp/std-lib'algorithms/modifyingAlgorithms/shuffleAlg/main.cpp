#include <algorithm>
#include <print>
#include <vector>
#include <random>

using namespace std;

int main()
{
   vector values{1, 2, 3, 4, 5, 6, 7, 8, 9};

   random_device seeder;
   default_random_engine generator{seeder()};

   for (int i{0}; i < 6; ++i)
   {
      shuffle(begin(values), end(values), generator);
      for (const auto &item: values)
      {
         print("{} ", item);
      }

      println();
   }
}
