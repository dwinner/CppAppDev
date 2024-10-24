#include <vector>
#include <print>

using namespace std;

int main()
{
   vector<int> intVec{1, 2, 3, 4, 5, 6, 7, 8, 10};
   auto oddPred = [](auto vecItem)
   {
      return vecItem % 2 != 0;
   };
   auto erasedCount = std::erase_if(intVec, oddPred);
   println("Removed items count = {}", erasedCount);
   for (const auto &item: intVec)
   {
      println("{}", item);
   }
}
