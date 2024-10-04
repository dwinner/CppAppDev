import std;
import kv;

using namespace std;
using namespace keyVal;

int main()
{
   const KeyValuePair intToFlt(1, 7E-1F);
   println("Key: {}, Value: {}", intToFlt.getKey(), intToFlt.getVal());

   // violated: const KeyValuePair<int, string> intToStr(1,"one");
}
