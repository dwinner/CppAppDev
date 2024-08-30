#include <iostream>
#include <format>

using namespace std;

int main()
{
   const string toParse{"   123USD"};
   size_t index{0};
   int value{stoi(toParse, &index)};
   cout << std::format("Parsed value: {}", value) << endl;
   cout << std::format("First non-parsed character: '{}'", toParse[index]) << endl;

   return 0;
}
