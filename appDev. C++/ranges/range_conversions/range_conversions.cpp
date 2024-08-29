import std;

using namespace std;

void printRange(string_view message, auto&& range)
{
   println("{}", message);
   for (const auto& item : range)
   {
      print("{} ", item);
   }
}

int main()
{
   // Convert a vector to a set with the same element type.
   vector vec{ 33, 11, 22 };
   auto s1{ ranges::to<set>(vec) };
   printRange(""sv, s1); // 11, 22, 33

   // Convert a vector of integers to a set of doubles, using the pipe operator.
   auto s2{ vec | ranges::to<set<double>>() };
   printRange(""sv, s2); // 11, 22, 33

   // Convert a vector of integers to a set of doubles, using from_range constructor.
   set<double> s3{ from_range, vec };
   printRange(""sv, s3); // 11, 22, 33

   // Lazily generate the integers from 10 to 14, divide these by 2,
   // and store the result in a vector of doubles.
   auto vec2{ views::iota(10, 15)
      | views::transform([](const auto& v) { return v / 2.0; })
      | ranges::to<vector<double>>() };
   printRange(""sv, vec2); // 5, 5.5, 6, 6.5, 7

   // Use views::split() and views::transform() to create a view
   // containing individual words of a string, and then convert
   // the resulting view to a vector of strings containing all the words.
   string lorem{ "Lorem ipsum dolor sit amet" };
   auto words{ lorem | views::split(' ')
      | views::transform([](const auto& v) { return string{ from_range, v }; })
      | ranges::to<vector>() };
   printRange(""sv, words); // "Lorem", "ipsum", "dolor", "sit", "amet"

   // Demonstrate xyz_range() member functions.
   vector<int> vec3;
   vec3.append_range(views::iota(10, 15));
   printRange(""sv, vec3); // 10, 11, 12, 13, 14
   vec3.insert_range(begin(vec3), views::iota(10, 15) | views::reverse);
   printRange(""sv, vec3); // 14, 13, 12, 11, 10, 10, 11, 12, 13, 14
}
