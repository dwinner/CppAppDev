#include <iostream>
#include "assocArray.hpp"

using namespace std;

int main()
{
   AssocArray<int> myArray;
   myArray["Key 1"] = 11;
   myArray["Key 2"] = 22;
   myArray["Key 3"] = 33;

   try
   {
      cout << myArray["Key 1"] << endl;
      cout << myArray["Key 2"] << endl;

      // Test const operator[]
      const AssocArray<int> &c{myArray};
      cout << c["Key 3"] << endl;
      cout << c["Key 4"] << endl;
   }
   catch (const invalid_argument &ex)
   {
      cout << "Caught exception: " << ex.what();
   }

   return 0;
}
