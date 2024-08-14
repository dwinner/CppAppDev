import std;

decltype(auto) Add(const auto& t1, const auto& t2)
{
   return t1 + t2;
}

int main()
{
   std::println("{}", Add(2, 4));
}
