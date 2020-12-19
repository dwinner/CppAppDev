#include <iostream>

#include "Timer.h"

int main()
{
   using std::cout;
   using std::endl;
   const Timer aida(3, 35);
   const Timer tosca(2, 48);

   cout << "Aida and Tosca:\n";
   cout << aida << "; " << tosca << endl;
   auto temp = aida + tosca; // operator+()
   cout << "Aida + Tosca: " << temp << endl;
   temp = aida * 1.17; // member operator*()
   cout << "Aida * 1.17: " << temp << endl;
   cout << "10.0 * Tosca: " << 10.0 * tosca << endl;

   return 0;
}
