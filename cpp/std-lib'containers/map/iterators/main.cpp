#include <iostream>
#include <map>
#include <print>

using namespace std;

class Data final
{
public:
   explicit Data(int value = 0) :
       val_{value}
   {
   }

   int getValue() const
   {
      return val_;
   }

   void setValue(int value)
   {
      val_ = value;
   }

private:
   int val_;
};

int main()
{
   map<int, Data> dataMap;

   dataMap[1] = Data{4};
   dataMap[1] = Data{6}; // Replaces the element with key 1

   // Using auto keyword
   for (auto iter{cbegin(dataMap)}; iter != cend(dataMap); ++iter)
   {
      println("{}", iter->second.getValue());
   }

   // Using range-based for loop
   for (const auto &mapItem: dataMap)
   {
      println("{}", mapItem.second.getValue());
   }

   // Using range-based for loop + structured bindings
   for (const auto &[key, data]: dataMap)
   {
      println("{}", data.getValue());
   }

   // Using iterators without auto.
   for (map<int, Data>::const_iterator iter{dataMap.begin()};
        iter != dataMap.end();
        ++iter)
   {
      println("{}", iter->second.getValue());
   }
}
