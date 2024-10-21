#include <iostream>
#include <vector>
#include <print>

using namespace std;

void printVector(const auto &collection)
{
   for (const auto &item: collection)
   {
      print("{} ", item);
   }

   println();
}

int main()
{
   {
      // Assign
      vector<int> intVector(10);
      println("intVector");  // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      printVector(intVector);

      // other code...
      intVector.assign(5, 100);
      println("intVector");  // 100, 100, 100, 100, 100
      printVector(intVector);

      intVector.assign({1, 2, 3, 4});
      println("intVector");  // 1, 2, 3, 4
      printVector(intVector);
   }

   {
      // Swap
      vector<int> vectorOne(10);
      vector<int> vectorTwo(5, 100);
      println("vectorOne");  // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      printVector(vectorOne);

      println("vectorTwo");  // 100, 100, 100, 100, 100
      printVector(vectorTwo);

      vectorOne.swap(vectorTwo);

      println("vectorOne");  // 100, 100, 100, 100, 100
      printVector(vectorOne);

      println("vectorTwo");  // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      printVector(vectorTwo);
   }
}
