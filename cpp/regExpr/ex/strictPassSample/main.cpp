#include <regex>
#include <print>
#include <iostream>

using namespace std;

int main()
{
   regex strictPassRegEx{
       "(?=(?:.*\\d){2})(?=.*[[:lower:]])(?=.*[[:upper:]])(?=.*[[:punct:]]).{8,}"
   };
   while (true)
   {
      print("Enter a password (q=quit): ");
      string str;
      if (!getline(cin, str) || str == "q")
      {
         break;
      }

      if (regex_match(str, strictPassRegEx))
      {
         println("  Valid password.");
      }
      else
      {
         println("  Invalid password!");
      }
   }
}