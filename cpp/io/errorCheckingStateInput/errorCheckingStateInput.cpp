import std;

using namespace std;

int main()
{
   println("Enter numbers on separate lines to add.");
   println("Use Control+D followed by Enter to finish (Control+Z in Windows).");
   int sum{0};

   if (!cin.good())
   {
      println(cerr, "Standard input is in a bad state!");
      return 1;
   }

   while (!cin.bad())
   {
      int number;
      cin >> number;
      if (cin.good())
      {
         sum += number;
      }
      else if (cin.eof())
      {
         break; // Reached end-of-file.
      }
      else if (cin.fail())
      {
         // Failure!
         cin.clear(); // Clear the failure state.
         string bad_token;
         cin >> bad_token; // Consume the bad input.
         println(cerr, "WARNING: Bad input encountered: {}", bad_token);
      }
   }

   println("The sum is {}.", sum);
}
