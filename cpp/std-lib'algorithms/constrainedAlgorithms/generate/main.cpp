#include <vector>
#include <ranges>
#include <print>
#include <algorithm>

using namespace std;

template<typename T>
void printVec(const vector<T> &vector)
{
   for (const auto &item: vector)
   {
      print("'{}' ", item);
   }

   println();
}

int main()
{
   {
      auto nextNumber{
          [counter = 0]() mutable
          { return ++counter; }
      };

      vector<int> values(10);
      ranges::generate(values, nextNumber);
      println("Vector contains:");
      printVec(values);

      print("Four more next numbers: ");
      for (unsigned i{0}; i < 4; ++i)
      {
         print("{}, ", nextNumber());
      }

      println("");
   }

   println("");

   // Passing a reference to the lambda expression.
   {
      auto nextNumber{
          [counter = 0]() mutable
          { return ++counter; }};

      vector<int> values(10);
      ranges::generate(values, ref(nextNumber));
      println("Vector contains");
      printVec(values);

      print("Four more next numbers: ");
      for (unsigned i{0}; i < 4; ++i)
      {
         print("{}, ", nextNumber());
      }

      println("");
   }
}