#include <iostream>
#include <vector>
#include <print>
#include <deque>
#include <algorithm>

using namespace std;

template<typename T>
void print_q(const deque<T> &deq)
{
   for (const auto &item: deq)
   {
      print("'{}' ", item);
   }

   println();
}

int main()
{
   const int cnt = 20;
   vector<int> values(cnt);
   for (int i = 0; i < cnt; ++i)
   {
      values[i] = i + 1;
   }

   //ranges::iota(values, 1);

   deque<int> evens, odds;
   ranges::partition_copy(
       values,
       back_inserter(evens),
       front_inserter(odds),
       [](int i)
       { return i % 2 == 0; });

   println("Even numbers:");
   print_q(evens);

   println("Odd numbers:");
   print_q(odds);
}
