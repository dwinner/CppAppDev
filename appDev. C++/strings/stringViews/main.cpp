#include <iostream>
#include <format>

using namespace std;

string extractExtension(string_view filename)
{
   // Return a copy of the extension.
   return string{filename.substr(filename.rfind('.'))};
}

int main()
{
   {
      // C++ std::string.
      string filename{R"(c:\temp\my file.ext)"};
      cout << std::format("C++ string: {}", extractExtension(filename)) << endl;

      // C-style string.
      const char *cString{R"(c:\temp\my file.ext)"};
      cout << std::format("C string: {}", extractExtension(cString)) << endl;

      // String literal.
      cout << std::format("Literal: {}", extractExtension(R"(c:\temp\my file.ext)")) << endl;

      // Raw string buffer with given length.
      const char *raw{"test.ext"};
      size_t length{8};
      cout << std::format("Raw: {}", extractExtension({raw, length})) << endl;
      cout << std::format("Raw: {}", extractExtension(string_view{raw, length})) << endl;
   }

   {
      // Concatenation with string_view.
      string str{"Hello"};
      string_view sv{" world"};
      //auto result{ str + sv };  // Error, does not compile!
      auto result1{str + string{sv}};

      string result2{str};
      result2.append(sv.data(), sv.size());

      cout << std::format("{}\n{}", result1, result2) << endl;
   }

   {
      // Using the standard user-defined literal sv.
      auto sv{"My string_view"sv};
   }

   return 0;
}
