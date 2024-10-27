#include <print>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

int main()
{
   vector values{1, 2, 3, 4, 5, 6, 7, 8, 9};
   const size_t numberOfSamples{5};
   vector<int> samples(numberOfSamples);

   random_device seeder;
   default_random_engine generator{seeder()};

   for (int i{0}; i < 6; ++i)
   {
      sample(cbegin(values), cend(values), begin(samples), numberOfSamples, generator);
      for (const auto &item: samples)
      {
         print("{} ", item);
      }

      println();
   }
}
