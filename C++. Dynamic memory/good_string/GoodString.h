#ifndef GOOD_STRING_GOODSTRING_H
#define GOOD_STRING_GOODSTRING_H

#include <iostream>
using std::ostream;
using std::istream;

class GoodString
{
public:
   // constructors and other methods

   explicit GoodString(const char* a_string); // constructor

   GoodString(); // default constructor

   GoodString(const GoodString& a_string); // copy constructor

   ~GoodString(); // destructor

   int length() const
   {
      return string_length_;
   }

   // overloaded operator methods

   GoodString& operator=(const GoodString& a_string);

   GoodString& operator=(const char* char_array);

   char& operator[](int an_index);

   const char& operator[](int an_index) const;

   // overloaded operator friends

   friend bool operator<(const GoodString& first_str, const GoodString& second_str);

   friend bool operator>(const GoodString& first_str, const GoodString& second_str);

   friend bool operator==(const GoodString& first_str, const GoodString& second_str);

   friend ostream& operator<<(ostream& out_stream, const GoodString& a_string);

   friend istream& operator>>(istream& in_stream, GoodString& a_string);

   // static function
   static int howMany();

private:
   char* string_ptr_; // pointer to string
   int string_length_; // length of string
   static int num_strings_; // number of objects
   static const int cinlim = 80; // cin input limit
};

#endif //GOOD_STRING_GOODSTRING_H
