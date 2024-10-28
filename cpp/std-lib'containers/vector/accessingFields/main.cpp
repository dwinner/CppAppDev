#include <print>
#include <vector>

using namespace std;

int main()
{
   vector<string> stringVector(10, "hello");

   for (auto it{begin(stringVector)};
        it != end(stringVector);
        ++it)
   {
      it->append(" there");
   }
}
