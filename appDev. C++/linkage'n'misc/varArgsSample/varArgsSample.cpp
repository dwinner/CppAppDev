import std;
#include <cstdarg>
#include <cstdio>

using namespace std;

bool Debug{false};

void DebugOut(const char* str, ...)
{
   if (Debug)
   {
      va_list ap;
      va_start(ap, str);
      vfprintf(stderr, str, ap);
      va_end(ap);
   }
}

void PrintInts(unsigned num, ...)
{
   va_list ap;
   va_start(ap, num);
   for (unsigned i{0}; i < num; ++i)
   {
      int temp{va_arg(ap, int)};
      print("{} ", temp);
   }

   va_end(ap);
   println("");
}

int main()
{
   Debug = true;
   DebugOut("int %d\n", 5);
   DebugOut("String %s and int %d\n", "hello", 5);
   DebugOut("Many ints: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);

   PrintInts(5, 5, 4, 3, 2, 1);
}
