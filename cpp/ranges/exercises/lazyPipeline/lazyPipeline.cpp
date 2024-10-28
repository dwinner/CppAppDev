import std;

using namespace std;

void PrintRange(string_view message, auto&& range)
{
   println("{}", message);
   for (const auto& item : range)
   {
      print("{} ", item);
   }
}

int main()
{
   auto result{
      views::iota(10, 101)
      | views::transform([](const auto& val)
      {
         return static_cast<int>(::pow(val, 2));
      })
      | views::filter([](const auto& val)
      {
         return val % 5 != 0;
      })
      | views::transform([](const auto& val)
      {
         return to_string(val);
      })
   };

   PrintRange("Range", result);
}
