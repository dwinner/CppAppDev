#include <iostream>
#include <cstring>
#include <format>

using namespace std;

#if defined(_MSC_VER)
// Disable the following Microsoft Visual C++ warning for this example:
   // C4996: 'xyz': This function or variable may be unsafe. Consider using xyz_s instead.
#pragma warning( disable : 4996)
#endif

char *copyString(const char *str)
{
   //char* result{ new char[strlen(str)] };  // BUG! Off by one!
   char *result{new char[strlen(str) + 1]};
   strcpy(result, str);

   return result;
}

char *appendStrings(const char *str1, const char *str2, const char *str3)
{
   char *result{new char[strlen(str1) + strlen(str2) + strlen(str3) + 1]};
   strcpy(result, str1);
   strcat(result, str2);
   strcat(result, str3);

   return result;
}

int main()
{
   const char *str1{"Hello"};
   char *copy{copyString(str1)};
   cout << std::format("{}", copy) << endl;
   delete[] copy;
   copy = nullptr;

   const char *str2{" World"};
   const char *str3{"!"};
   char *result{appendStrings(str1, str2, str3)};
   cout << std::format("{}", result) << endl;
   delete[] result;
   result = nullptr;

   char text1[]{"abcdef"};
   size_t s1{sizeof(text1)};  // is 7
   size_t s2{strlen(text1)};  // is 6
   cout << std::format("{}\n{}", s1, s2) << endl;

   const char *text2{"abcdef"};
   size_t s3{sizeof(text2)};  // is platform-dependent (e.g. 4 bytes for x86, 8 bytes for x64)
   size_t s4{strlen(text2)};  // is 6
   cout << std::format("{}\n{}", s3, s4) << endl;

   return 0;
}
