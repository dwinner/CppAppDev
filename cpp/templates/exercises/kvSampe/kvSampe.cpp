import std;
import kv;

using namespace std;
using namespace keyVal;

int main()
{
   const auto intToStrKv = make_unique<KeyValuePair<int, string>>(1, "one");
   println("Key: {}. Value: {}.", intToStrKv->getKey(), intToStrKv->getVal());
   intToStrKv->setKey(2);
   intToStrKv->setVal("two");
   println("Key: {}. Value: {}.", intToStrKv->getKey(), intToStrKv->getVal());

   const KeyValuePair strToStr("hi", "there");
   println("Key: {}. Value: {}.", strToStr.getKey(), strToStr.getVal());

   const KeyValuePair intToStr(0, "zero");
   println("Key: {}. Value: {}.", intToStr.getKey(), intToStr.getVal());

   const KeyValuePair strToInt("zero", 0);
   println("Key: {}. Value: {}.", strToInt.getKey(), strToInt.getVal());

   const KeyValuePair intToDblKv(3, 0.3);
   println("Key: {}. Value: {}.", intToDblKv.getKey(), intToDblKv.getVal());
}
