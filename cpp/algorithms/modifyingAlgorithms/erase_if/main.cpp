#include <print>
#include <vector>
#include <string>

using namespace std;

int main()
{
   vector<string> values{"", "one", "", "two", "three", "four"};

   for (const auto &item: values)
   {
      print("'{}' ", item);
   }

   erase_if(values, [](const string &str)
   {
      return str.empty();
   });

   println();

   for (const auto &item: values)
   {
      print("'{}' ", item);
   }
}
