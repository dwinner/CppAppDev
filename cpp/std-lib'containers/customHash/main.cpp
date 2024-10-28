#include <iostream>
#include <set>
#include <unordered_set>
#include <print>

using namespace std;

class IntWrapper
{
public:
   explicit IntWrapper(int i) :
       wrappedInt_{i}
   {
   }

   int getValue() const
   {
      return wrappedInt_;
   }

   bool operator==(const IntWrapper &) const = default;// = default since C++20

private:
   int wrappedInt_;
};

namespace std
{
   template<>
   struct hash<IntWrapper>
   {
      size_t operator()(const IntWrapper &x) const
      {
         return std::hash<int>{}(x.getValue());
      }
   };
}

int main()
{
   unordered_set<IntWrapper> s;
   s.insert(IntWrapper{1});
   s.insert(IntWrapper{2});

   for (const auto &element: s)
   {
      println("{}", element.getValue());
   }
}
