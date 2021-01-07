#include "BadString.h"
#include <cstring>

using std::cout;

int BadString::num_strings = 0;

BadString::BadString(const char *s)
{
   len = std::strlen(s);  // set size
   str = new char[len + 1]; // alloc storage
   std::strcpy(str, s); // init pointer
   num_strings++;       // set object count
   cout << num_strings << ": " << str << "\" object created\n";
}

BadString::BadString()                // default constructor
{
   len = 4;
   str = new char[4];
   std::strcpy(str, "C++");          // default string
   num_strings++;
   cout << num_strings << ": \"" << str << "\" default object created\n";  // FYI
}

BadString::~BadString()               // necessary destructor
{
   cout << "\"" << str << "\" object deleted, ";    // FYI
   --num_strings;                    // required
   cout << num_strings << " left\n"; // FYI
   delete[] str;                    // required
}

std::ostream &operator<<(std::ostream &os, const BadString &st)
{
   os << st.str;
   return os;
}
