#include <iostream>
#include <map>
#include <print>

using namespace std;

template<typename TKey, typename TVal>
void printMap(std::map<TKey, TVal> aMap)
{
   for (const auto &item: aMap)
   {
      println("{} -> {}", item.first, item.second);
   }
}

int main()
{
   map<int, int> src
       {
           {1, 11},
           {2, 22}
       };
   map<int, int> dst
       {
           {2, 22},
           {3, 33},
           {4, 44},
           {5, 55}
       };
   dst.merge(src);

   println("src:");
   printMap(src);

   println("dst:");
   printMap(dst);
}
