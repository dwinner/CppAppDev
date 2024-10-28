#include <print>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function template to populate a container of ints.
// A constraint enforces that the container supports push_back(int).
template<typename Container>
requires
requires(Container &container, int i)
{
   container.push_back(i);
}
void populateContainer(Container &cont)
{
   while (true)
   {
      print("Enter a number (0 to stop): ");
      int value;
      cin >> value;
      if (value == 0)
      {
         break;
      }

      cont.push_back(value);
   }
}

template<typename T>
void printVec(vector<T> vector)
{
   for (const auto &item: vector)
   {
      print("'{}' ", item);
   }

   println();
}

int main()
{
   vector<int> values, vecOdd, vecEven;

   populateContainer(values);

   vecOdd.resize(size(values));
   vecEven.resize(size(values));

   auto pairIters{
       partition_copy(
           cbegin(values),
           cend(values),
           begin(vecEven),
           begin(vecOdd),
           [](int i)
           {
              return i % 2 == 0;
           })
   };

   vecEven.erase(pairIters.first, end(vecEven));
   vecOdd.erase(pairIters.second, end(vecOdd));

   println("Even numbers:");
   printVec(vecEven);

   println("Odd numbers:");
   printVec(vecOdd);
}
