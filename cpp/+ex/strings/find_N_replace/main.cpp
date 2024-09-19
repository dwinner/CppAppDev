#include <print>

using namespace std;

std::string replaceAll(string inputStr, string_view fromStr, string_view toStr);

int main()
{
   string input = "This is 'long' text with 'long' word";
   string from = "long";
   string to = "int";
   string replaced = replaceAll(input, from, to);

   println("Replaced: {}", replaced);

   return 0;
}

std::string replaceAll(string inputStr, string_view fromStr, string_view toStr)
{
   if (fromStr.empty())
   {
      return inputStr;
   }

   size_t start_pos = 0;
   while ((start_pos = inputStr.find(fromStr, start_pos)) != std::string::npos)
   {
      inputStr.replace(start_pos, fromStr.length(), toStr);
      start_pos += toStr.length();
   }

   return std::move(inputStr);
}
