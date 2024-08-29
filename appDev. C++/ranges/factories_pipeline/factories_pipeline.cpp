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
	auto result{ views::iota(10)
		| views::filter([](const auto& value) {return value % 2 == 0; })
		| views::transform([](const auto& value) {return value * 2.0; })
		| views::take(10) };
	printRange("<- Result", result);
}
