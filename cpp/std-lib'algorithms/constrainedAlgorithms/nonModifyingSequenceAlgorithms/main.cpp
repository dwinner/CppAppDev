#include <vector>
#include <ranges>
#include <algorithm>
#include <print>

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
   vector values{11, 22, 33, 44, 55};
   vector v{11, 22};
   printVec(values);
   println("contains 33 = {}", ranges::contains(values, 33));
   printVec(v);
   println("contains = {}", ranges::contains_subrange(values, v));
   println("{} starts with", ranges::starts_with(values, v));
}
