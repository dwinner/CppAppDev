#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printSequence(const auto &seq)
{
   for (const auto &item: seq)
   {
      std::cout << item << ' ';
   }

   std::cout << '\n';
}

int main()
{
   // Legacy way
   vector<int> vec1St = {3, 4, 5, 7};  // must be sorted
   do
   {
      printSequence(vec1St);
   }
   while (next_permutation(vec1St.begin(), vec1St.end()));

   // Modern way
   vector<int> vec2Nd = {1, 2, 3};
   do
   {
      printSequence(vec2Nd);
   }
   while (std::ranges::next_permutation(vec2Nd).found);
}
