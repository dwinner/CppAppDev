#include <vector>
#include <print>

using namespace std;

int main()
{
   vector<int> intVector(10, 100); // Creates a vector of 10 ints with value 100
   for (const auto &item: intVector)
   {
      println("{}", item);
   }
}
