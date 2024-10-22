#include <iostream>
#include <map>

using namespace std;

class Data final
{
public:
   explicit Data(int value = 0) : val_{value}
   {}

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
   return 0;
}
