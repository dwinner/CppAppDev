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

   println("There are {} elements with key 1.", dataMap.count(1));
   dataMap.erase(1);
   println("There are {} elements with key 1.", dataMap.count(1));
}
