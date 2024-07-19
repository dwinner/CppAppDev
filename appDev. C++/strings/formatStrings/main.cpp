#include <iostream>

using namespace std;

int main()
{
   int n{ 42 };

	println("Read {} bytes from {}", n, "file1.txt");
	println("Read {0} bytes from {1}", n, "file1.txt");
	println("从{1}中读取{0}个字节。", n, "file1.txt");

   int x{ 42 };
   int y{ 84 };
   println(cerr, "x has value {} and y has value {}.", x, y);

   // compile time checks
   {
      string s{ "Hello World!" };
      //println(s);   // Error! Does not compile.
      println("{}", s);
   }

   {
      constexpr auto formatString{ "Value: {}" };
      println(formatString, 11);  // Value: 11
   }

   return 0;
}
