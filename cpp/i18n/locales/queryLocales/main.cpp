#include <print>

using namespace std;

int main()
{
   locale loc{""};
   //string locName = loc.name();

   if (loc.name().find("en_US") == string::npos
       && loc.name().find("en-US") == string::npos)
   {
      println("Welcome non-US English speaker!");
   }
   else
   {
      println("Welcome US English speaker!");
   }
}
