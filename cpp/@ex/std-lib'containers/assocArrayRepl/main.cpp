#include <iostream>
#include <map>

using namespace std;

int main()
{
   map<string, int> strToIntMap;
   strToIntMap["Key 1"] = 11;
   strToIntMap["Key 2"] = 22;
   strToIntMap["Key 3"] = 33;
   cout << strToIntMap["Key 1"] << endl;
   cout << strToIntMap["Key 2"] << endl;

   /*const */map<string, int> &copied{strToIntMap};
   const int k3Val = copied["Key 3"];
   const int k4Val = copied["Key 4"];
   cout << k3Val << endl;
   cout << k4Val << endl;

   return 0;
}
