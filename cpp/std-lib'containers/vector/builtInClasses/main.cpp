#include <vector>
#include <print>

using namespace std;

int main()
{
   vector<string> stringVector(10, "hello");
   for (const auto &item: stringVector)
   {
      println("{}", item);
   }
}
