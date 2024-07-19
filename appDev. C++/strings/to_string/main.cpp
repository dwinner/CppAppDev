#include <iostream>
#include <format>

using namespace std;

int main()
{
   long double d{3.14L};
   string s{to_string(d)};  // s contains 3.140000
   cout << std::format("{}", s) << endl;

   return 0;
}
