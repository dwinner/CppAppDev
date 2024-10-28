#include <regex>
#include <print>
#include <iostream>

using namespace std;

int main()
{
   regex srcCodeRegEx{"^(.*?)//.*$"};
   const string replacement{"$1"};
   while (true)
   {
      println("Enter a source code snippet, terminated with @:");
      string str;
      if (!getline(cin, str, '@'))
      {
         break;
      }

      println("{}", regex_replace(str, srcCodeRegEx, replacement));
   }
}