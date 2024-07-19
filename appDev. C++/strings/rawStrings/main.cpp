#include <iostream>
#include <format>

int main()
{
   //std::cout<<std::format("Hello "World"!");    // Error!
   std::cout << std::format("Hello \"World\"!") << std::endl;
   std::cout << std::format(R"(Hello "World"!)") << std::endl;

   std::cout << std::format("Line 1\nLine 2") << std::endl;
   std::cout << std::format(R"(Line 1
Line 2)") << std::endl;

   std::cout << std::format(R"(Is the following a tab character? \t)") << std::endl;

   //std::cout<<std::format(R"(Embedded )" characters)");    // Error!
   std::cout << std::format(R"-(Embedded )" characters)-") << std::endl;

   return 0;
}
