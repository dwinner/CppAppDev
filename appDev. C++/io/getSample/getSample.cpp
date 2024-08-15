import std;

using namespace std;

string read_name(istream& stream);

int main()
{
   println("Type a name followed by Enter followed by Control+D (Control+Z in Windows) and another Enter: ");
   string theName{read_name(cin)};

   println("The name is \"{}\".", theName);
}


string read_name(istream& stream)
{
   string name;
   while (stream)
   {
      // Or: while (!stream.fail()) {
      int next{stream.get()};
      if (!stream || next == std::char_traits<char>::eof())
      {
         break;
      }

      name += static_cast<char>(next); // Append character.
   }

   return name;
}
