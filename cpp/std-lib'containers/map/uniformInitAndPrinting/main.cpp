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
   map<string, int> m
       {
           {"Marc G.",    12},
           {"Warren B.",  34},
           {"Peter V.W.", 56}
       };

   for (const auto &p: m)
   {
      println("{} = {}", p.first, p.second);
   }

   println("");
   printMap(m);
}
