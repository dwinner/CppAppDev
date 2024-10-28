#include <print>
#include <vector>

using namespace std;

int main()
{
   vector<string> vec;

   // push_back will trigger copying
   string myElement(5, 'a');  // Constructs the string "aaaaa"
   vec.push_back(myElement);

   // no copying, due to move semantics
   vec.push_back(std::move(myElement));
   vec.push_back(string(5, 'a'));
}
