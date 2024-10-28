#include <iostream>
#include <print>
#include <vector>
#include <iterator>

using namespace std;

size_t findMaxLen(vector<string> inputVector);

int main()
{
   println("Enter strings until '*' is hit");

   vector<string> strings;
   string inputStr;
   cin >> inputStr;
   while (inputStr != "*")
   {
      strings.emplace_back(inputStr);
      cin >> inputStr;
   }

   const size_t width = findMaxLen(strings);
   for (const auto &item: strings)
   {
      print("|{1:{0}s}| ", width, item);
   }

   return 0;
}

size_t findMaxLen(vector<string> inputVector)
{
   if (inputVector.empty())
   {
      return 0;
   }

   auto foundIt = max_element(inputVector.begin(), inputVector.end(),
                              [](const auto &str1, const auto &str2)
                              {
                                 return str1.size() < str2.size();
                              });

   return foundIt->length();
}
