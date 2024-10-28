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

   map<int, Data> dataMap2;

   //auto extractedNode{ dataMap.extract(1) };
   //dataMap2.insert(move(extractedNode));

   dataMap2.insert(dataMap.extract(1));

   return 0;
}
