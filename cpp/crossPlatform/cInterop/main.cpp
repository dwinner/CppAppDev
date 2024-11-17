#include <print>
#include "reverseString.h"

using namespace std;

/**
 * @brief A wrapper class for the C reverseString library.
 */
class ReverseString
{
public:
   explicit ReverseString(const string &str)
   {
      unique_ptr<char[], decltype(&freeString)> reversedString{
          reverseString(str.c_str()),
          freeString
      };
      reversedString_ = reversedString.get();
   }

   const string &getReversedString() const
   {
      return reversedString_;
   }

private:
   string reversedString_;
};


int main()
{
   ReverseString reverser{"Hello World!"};
   println("{}", reverser.getReversedString());
}
