#include <print>
#include <vector>

using namespace std;

void printColl(const auto &collection)
{
   for (const auto &item: collection)
   {
      print("{} ", item);
   }

   println();
}

int main()
{
   vector values{1, 2, 3, 2, 1, 2, 4, 5};
   printColl(values);

   erase(values, 2);  // Removes all values equal to 2.
   printColl(values);
}
