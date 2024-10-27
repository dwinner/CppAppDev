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
   vector values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   println("Before:");
   printVec(values);

   ranges::for_each(
       values |
       views::filter([](int value)
                     {
                        return value % 2 == 0;
                     }),
       [](int &value)
       {
          value *= 10;
       }
   );
   println("After:");
   printVec(values);
}
