#include <cstring>
#include "GoodString.h"

using std::cin;
using std::cout;

// initializing static class member

int GoodString::num_strings_ = 0;

// static method
int GoodString::howMany()
{
   return num_strings_;
}

// class methods
GoodString::GoodString(const char* a_string) // construct String from C string
{
   string_length_ = std::strlen(a_string); // set size
   string_ptr_ = new char[string_length_ + 1]; // alloc storage   
   strcpy_s(string_ptr_, string_length_, a_string); // initialize pointer
   num_strings_++; // set object count
}

GoodString::GoodString() // default constructor
{
   string_length_ = 4;
   string_ptr_ = new char[1];
   string_ptr_[0] = '\0'; // default string
   num_strings_++;
}

GoodString::GoodString(const GoodString& a_string)
{
   num_strings_++; // handle static member update
   string_length_ = a_string.string_length_; // same length
   string_ptr_ = new char [string_length_ + 1]; // alloc space
   strcpy_s(string_ptr_, string_length_, a_string.string_ptr_); // copy string to new location
}

GoodString::~GoodString() // necessary destructor
{
   --num_strings_; // required
   delete [] string_ptr_; // required
}

// overloaded operator methods

// assign a String to a String
GoodString& GoodString::operator=(const GoodString& a_string)
{
   if (this == &a_string)
   {
      return *this;
   }

   delete [] string_ptr_;
   string_length_ = a_string.string_length_;
   string_ptr_ = new char[string_length_ + 1];
   strcpy_s(string_ptr_, string_length_, a_string.string_ptr_);

   return *this;
}

// assign a C string to a String
GoodString& GoodString::operator=(const char* char_array)
{
   delete [] string_ptr_;
   string_length_ = std::strlen(char_array);
   string_ptr_ = new char[string_length_ + 1];
   strcpy_s(string_ptr_, string_length_, char_array);

   return *this;
}

// read-write char access for non-const String
char& GoodString::operator[](const int an_index)
{
   return string_ptr_[an_index];
}

// read-only char access for const String
const char& GoodString::operator[](const int an_index) const
{
   return string_ptr_[an_index];
}

// overloaded operator friends

bool operator<(const GoodString& first_str, const GoodString& second_str)
{
   return std::strcmp(first_str.string_ptr_, second_str.string_ptr_) < 0;
}

bool operator>(const GoodString& first_str, const GoodString& second_str)
{
   return second_str < first_str;
}

bool operator==(const GoodString& first_str, const GoodString& second_str)
{
   return std::strcmp(first_str.string_ptr_, second_str.string_ptr_) == 0;
}

// simple String output
ostream& operator<<(ostream& out_stream, const GoodString& a_string)
{
   out_stream << a_string.string_ptr_;
   return out_stream;
}

// quick and dirty String input
istream& operator>>(istream& in_stream, GoodString& a_string)
{
   char temp[GoodString::cinlim];
   in_stream.get(temp, GoodString::cinlim);
   if (in_stream)
   {
      a_string = temp;
   }

   while (in_stream && in_stream.get() != '\n')
   {
   }

   return in_stream;
}
