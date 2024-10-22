#include <iostream>
#include <map>
#include <print>

using namespace std;

void func(const map<int, int> &m)
{
   map<int, int> cMap = const_cast<map<int, int> &>(m);
   println("{0}", cMap[1]);
   //println("{}", m[1]);  // Error
}

int main()
{
   map<int, int> m;
   m[1] = 11;
   m[2] = 22;
   m[3] = 33;
   func(m);
}
