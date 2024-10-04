#include <iostream>
#include "Point3D.hpp"

using namespace std;

int main()
{
   auto point = make_unique<Point3D>(1, 2, 3);
   cout << *point;

   return 0;
}
