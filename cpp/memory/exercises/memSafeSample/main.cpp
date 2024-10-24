#include <print>

using namespace std;

void fillWithM(string &str);

int main()
{
   string text = "aa"s;
   fillWithM(text);
   std::println("{:s}", text);

   return 0;
}

void fillWithM(string &str)
{
   if (str.empty())
   {
      return;
   }

   for (auto &item: str)
   {
      item = 'm';
   }
}
