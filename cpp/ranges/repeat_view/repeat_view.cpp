import std;

using namespace std;

void printRange(string_view message, auto&& range)
{
   for (const auto& item : range)
   {
      print("{} ", item);
   }

   println("{}", message);
}

int main()
{
   // views::repeat
   printRange("<- Repeating view", views::repeat(42, 5));
}
