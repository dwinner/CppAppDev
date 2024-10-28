#include <print>
#include <vector>

using namespace std;

int main()
{
   vector<int> intVector;

   auto iter{end(intVector)};
   *iter = 10; // BUG! iter doesn't refer to a valid element.

   vector<int> vectorOne(10);
   vector<int> vectorTwo(10);

   // fixme - Possible infinite loop.
   for (auto iter{begin(vectorTwo)}; iter != end(vectorOne); ++iter)
   {
      /* ... */
   }
}
