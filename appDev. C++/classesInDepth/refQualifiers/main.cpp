#include <iostream>
#include <format>

using namespace std;

class TextHolder
{
public:
   explicit TextHolder(string text)
       : _text{std::move(text)}
   {}

   //const string& getText() const { return _text; }

   [[nodiscard]] const string &getText() const &
   {
      return _text;
   }

   string &&getText() &&
   {
      return std::move(_text);
   }

   TextHolder &operator=(const string &rhs) &
   {
      _text = rhs;
      return *this;
   }

private:
   string _text;
};

TextHolder makeTextHolder()
{
   return TextHolder{"Hello World!"};
}

int main()
{
   TextHolder textHolder{"Hello world!"};
   cout << format("{}", textHolder.getText()) << endl;
   cout << format("{}", TextHolder{"Hello world!"}.getText()) << endl;

   // Pointless, object is a temporary.
   //makeTextHolder() = "Pointless!";

   // Ok
   auto text{makeTextHolder()};
   text = "Ok";

   return 0;
}
