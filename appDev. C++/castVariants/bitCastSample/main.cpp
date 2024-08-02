#include <print>

using namespace std;

int main()
{
   float asFloat{1.23f};
   auto asUint{bit_cast<unsigned int>(asFloat)};
   if (bit_cast<float>(asUint) == asFloat)
   {
      println("Roundtrip success.");
   }

   return 0;
}
