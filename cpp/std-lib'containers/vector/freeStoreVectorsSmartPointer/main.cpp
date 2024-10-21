#include <iostream>
#include <vector>

using namespace std;

class Element
{
};

int main()
{
   auto elementVector{make_unique<vector<Element>>(10)};
}
