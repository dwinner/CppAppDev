#include <sstream>
#include <print>

using namespace std;

void print()
{
   stringstream stream;
   stream << 32767;
   println("{}", stream.str());
}

int main()
{
   print();

   /*auto old = */
   locale::global(locale{"en-US"}); // "en_US" for POSIX
   print();
}