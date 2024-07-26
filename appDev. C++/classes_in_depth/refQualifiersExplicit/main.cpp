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

   const string &getText(this const TextHolder &self)
   {
      return self._text;
   }

   string &&getText(this TextHolder &&self)
   {
      return move(self._text);
   }

   TextHolder &operator=(this TextHolder &self, const string &rhs)
   {
      self._text = rhs;
      return self;
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
   cout << std::format("{}", textHolder.getText()) << endl;
   cout << std::format("{}", TextHolder{"Hello world!"}.getText()) << endl;

   // Pointless, object is a temporary.
   //makeTextHolder() = "Pointless!";

   // Ok
   auto text{makeTextHolder()};
   text = "Ok";

   return 0;
}
