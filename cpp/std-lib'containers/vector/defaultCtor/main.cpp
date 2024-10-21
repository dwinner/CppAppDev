#include <vector>
#include <print>

using namespace std;

int main()
{
   vector<int> intVector; // Creates a vector of ints with zero elements
   for (const auto &item: intVector)
   {
      println("{}", item);
   }
}
