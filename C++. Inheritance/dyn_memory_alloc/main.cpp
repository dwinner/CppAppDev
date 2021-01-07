#include <iostream>
#include "DmaBase.h"
#include "LacksDma.h"
#include "HasDma.h"

int main()
{
   using std::cout;
   using std::endl;

   const DmaBase shirt("Portabelly", 8);
   const LacksDma balloon("red", "Blimpo", 4);
   const HasDma map("Mercator", "Buffalo Keys", 5);
   cout << "Displaying baseDMA object:\n";
   cout << shirt << endl;
   cout << "Displaying lacksDMA object:\n";
   cout << balloon << endl;
   cout << "Displaying hasDMA object:\n";
   cout << map << endl;
   const LacksDma balloon2(balloon);
   cout << "Result of lacksDMA copy:\n";
   cout << balloon2 << endl;
   const HasDma map2 = map;
   cout << "Result of hasDMA assignment:\n";
   cout << map2 << endl;

   return 0;
}
