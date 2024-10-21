#include <vector>
#include <print>

using namespace std;

int main()
{
   vector<int> intVector({1, 2, 3, 4, 5, 6});
   for (const auto &item: intVector)
   {
      println("{}", item);
   }
}
