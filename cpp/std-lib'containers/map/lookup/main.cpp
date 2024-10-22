#include <iostream>
#include <map>

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
   dataMap[1] = Data{6};
   dataMap[1].setValue(100);

   auto it{dataMap.find(1)};
   if (it != end(dataMap))
   {
      it->second.setValue(100);
   }

   dataMap.at(1).setValue(200);
}
