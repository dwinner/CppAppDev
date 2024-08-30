import std;

using namespace std;

constexpr size_t buffer_size{1024};

int main()
{
   println("Enter a line of text:");
   char buffer[buffer_size]{0};
   cin.getline(buffer, buffer_size);
   println("\"{}\"", buffer);

   println("");

   println("Enter another line of text:");
   string myString;
   getline(cin, myString);
   println("\"{}\"", myString);
}
