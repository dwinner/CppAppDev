#include <vector>
#include <print>

using namespace std;

int main()
{
   vector<int> values{2, 5};
   values.insert(cbegin(values) + 1, {3, 4});

   vector<int> vec2Nd{0, 1};
   values.insert(cend(values), cbegin(vec2Nd), cend(vec2Nd));

   vector<int> vec3Rd;

   for (auto rIter{cend(values) - 1};
        rIter != cbegin(values);
        --rIter)
   {
      vec3Rd.push_back(*rIter);
   }

   for (const auto &item: vec3Rd)
   {
      println("{}", item);
   }

   return 0;
}
