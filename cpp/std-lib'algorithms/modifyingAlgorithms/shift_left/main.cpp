#include <vector>
#include <print>
#include <algorithm>

using namespace std;

void printVec(const vector<int> &vec)
{
   for (const auto &item: vec)
   {
      print("{}, ", item);
   }

   println();
}

int main()
{
   vector values{11, 22, 33, 44, 55};
   printVec(values);

   // Shift elements to the left by 2 positions.
   auto newEnd{
       shift_left(begin(values), end(values), 2)
   };

   // Resize the vector to its proper size.
   values.erase(newEnd, end(values));
   printVec(values);

   // Shift elements to the right by 2 positions.
   auto newBegin{
       shift_right(begin(values), end(values), 2)
   };

   // Resize the vector to its proper size.
   values.erase(begin(values), newBegin);
   printVec(values);
}
