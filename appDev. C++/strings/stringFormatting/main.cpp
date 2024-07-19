#include <iostream>
#include <format>

using namespace std;

int main()
{
   int x{42};
   int y{84};

   // C-style function.
   printf("x has value '%d' and y has value '%d'.\n", x, y);

   // C++ I/O stream.
   cout << "x has value " << x << " and y has value " << y << '.' << endl;

   // C++20 std::format() + I/O streams.
   cout << std::format("x has value {} and y has value {}.", x, y) << endl;

   // C++23 std::cout << std::format() + Unicode.
   cout << std::format("こんにちは世界") << endl;

   // I/O streams + Unicode.
   cout << "こんにちは世界" << endl;

   // C++23 std::cout << std::format() + Unicode emojis.
   cout << std::format("😀") << endl;

   return 0;
}
