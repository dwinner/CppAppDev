#include <vector>
#include <algorithm>
#include <print>
#include <numeric>

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
   vector<int> values(10);
   iota(begin(values), end(values), 5);
   printVec(values);
}