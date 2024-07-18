#include <iostream>
#include <optional>
#include <format>

using namespace std;

optional<int> getData(bool giveIt)
{
   if (giveIt)
   {
      return 42;
   }

   return nullopt;  // or simply return {};
}

int main()
{
   optional<int> data1{getData(true)};
   optional<int> data2{getData(false)};

   cout << std::format("data1.has_value = {}", data1.has_value()) << endl;

   if (!data2)
   {
      cout << "data2 has no value." << endl;
   }

   cout << std::format("data1.value = {}", data1.value()) << endl;
   cout << std::format("data1.value = {}", *data1) << endl;

   try
   {
      cout << std::format("data2.value = {}", data2.value()) << endl;
   }
   catch (const bad_optional_access &ex)
   {
      cout << std::format("Exception: {}", ex.what()) << endl;
   }

   cout << std::format("data2.value = {}", data2.value_or(0)) << endl;

   return 0;
}
