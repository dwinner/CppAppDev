#include <print>
#include <functional>

using namespace std;

void func(int num, string_view str)
{
   println("func({}, {})", num, str);
}

int main()
{
   // Bind second argument to a fixed value.
   string myString{"abc"};
   auto f1{
       [myString](auto &&placeHolder1)
       {
          func(std::forward<decltype(placeHolder1)>(placeHolder1), myString);
       }
   };
   f1(16);

   // Rearrange arguments
   auto f2{
       [](auto &&placeHolder1, auto &&placeHolder2)
       {
          func(
              std::forward<decltype(placeHolder2)>(placeHolder2),
              std::forward<decltype(placeHolder1)>(placeHolder1)
          );
       }
   };
   f2("Test", 32);
}
