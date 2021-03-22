#include <iostream>

#ifndef BAD_STRING_BADSTRING_H
#define BAD_STRING_BADSTRING_H

class BadString
{
public:
   BadString(const char *s);  // ctor
   BadString();               // default ctor
   ~BadString();              // dtor

   // friend function
   friend std::ostream &operator<<(std::ostream &os, const BadString &st);

private:
   char *str;              // pointer to string
   int len;                // length of string
   static int num_strings; // number  of objects
};

#endif //BAD_STRING_BADSTRING_H
