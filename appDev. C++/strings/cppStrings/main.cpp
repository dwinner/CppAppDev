#include <iostream>
#include <format>

using namespace std;

int main()
{
   {
      string a{"12"};
      string b{"34"};
      string c{a + b};    // c is "1234"
      cout << std::format("{}", c) << endl;

      a += b;    // a is "1234"
      cout << std::format("{}", a) << endl;
   }

   cout << std::format("") << endl;

   {
      string a{"Hello"};
      string b{"World"};
      cout << std::format("'{}' < '{}' = {}", a, b, a < b) << endl;
      cout << std::format("'{}' > '{}' = {}", a, b, a > b) << endl;
   }

   cout << std::format("") << endl;

   {
      string a{"12"};
      string b{"34"};

      auto result{a.compare(b)};
      if (result < 0)
      {
         cout << std::format("less") << endl;
      }

      if (result > 0)
      {
         cout << std::format("greater") << endl;
      }

      if (result == 0)
      {
         cout << std::format("equal") << endl;
      }
   }

   cout << std::format("");

   {
      // C++20 three-way comparison operator
      string a{"12"};
      string b{"34"};
      auto result{a <=> b};
      if (is_gt(result))
      {
         cout << std::format("greater") << endl;
      }

      if (is_lt(result))
      {
         cout << std::format("less") << endl;
      }

      if (is_eq(result))
      {
         cout << std::format("equal") << endl;
      }
   }

   cout << std::format("") << endl;

   {
      string myString{"hello"};
      myString += ", there";
      string myOtherString{myString};
      if (myString == myOtherString)
      {
         myOtherString[0] = 'H';
      }

      cout << std::format("{}", myString) << endl;
      cout << std::format("{}", myOtherString) << endl;
   }

   cout << std::format("") << endl;

   {
      string strHello{"Hello!!"};
      string strWorld{"The World..."};
      auto position{strHello.find("!!")};
      if (position != string::npos)
      {
         // Found the "!!" substring, now replace it.
         strHello.replace(position, 2, strWorld.substr(3, 6));
      }
      cout << std::format("{}", strHello) << endl;

      // Test contains().
      string toFind{"World"};
      cout << std::format("{}", strWorld.contains(toFind)) << endl;  // true
      cout << std::format("{}", strWorld.contains('.')) << endl;     // true
      cout << std::format("{}", strWorld.contains("Hello")) << endl; // false
   }

   cout << std::format("") << endl;

   {
      auto string1{"Hello World"};    // string1 is a const char*.
      auto &string2{"Hello World"};   // string2 is a const char[12].
      auto string3{"Hello World"s};   // string3 is an std::string.
   }

   return 0;
}
