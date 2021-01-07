#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
   vector<string> input;
   string temp;
   while (cin >> temp && temp != "quit")
   {
      input.push_back(temp);
   }

   auto want = find(input.begin(), input.end(), string("bonus"));

   if (want != input.end())
   {
      vector<string>::reference r = *want;
      // readonly: reference_wrapper<string> otherRef = r;
      r = "bogus";
   }

   for_each(input.begin(), input.end(),
            [](const string &s)
            {
               cout << s << ", ";
            });

   return 0;
}
