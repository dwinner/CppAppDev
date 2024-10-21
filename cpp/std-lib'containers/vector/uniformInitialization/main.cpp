#include <print>
#include <vector>

using namespace std;

void printVector(const auto &collection);

int main()
{
   vector<int> intVector1 = {1, 2, 3, 4, 5, 6};
   vector<int> intVector2{1, 2, 3, 4, 5, 6};
   vector intVector3{1, 2, 3, 4, 5, 6};

   println("Vector 1 elements");
   printVector(intVector1);

   println("Vector 2 elements");
   printVector(intVector2);

   println("Vector 3 elements");
   printVector(intVector3);
}

void printVector(const auto &collection)
{
   for (const auto &item: collection)
   {
      println("{}", item);
   }
}
