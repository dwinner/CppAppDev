#include <regex>
#include <print>
#include <iostream>

using namespace std;

int main()
{
   regex phoneNumRegExpr{R"((\d{3})-(\d{3})-(\d{4}))"};
   while (true)
   {
      print("Enter a US phone number (xxx-xxx-xxxx) (q=quit): ");
      string str;
      if (!getline(cin, str) || str == "q")
      {
         break;
      }

      if (smatch matchResults;
          regex_match(str, matchResults, phoneNumRegExpr))
      {
         println("  Valid phone number:");
         println("{}\n{}\n{}",
                 matchResults[1].str(),
                 matchResults[2].str(),
                 matchResults[3].str());
      }
      else
      {
         println("  Invalid phone number!");
      }
   }
}