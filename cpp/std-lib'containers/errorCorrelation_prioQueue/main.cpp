#include <iostream>
#include "ErrorCorrelator.hpp"

using namespace std;

int main()
{
   ErrorCorrelator errorCorrelation;

   errorCorrelation.addError(Error{3, "Unable to read file"});
   errorCorrelation.addError(Error{1, "Incorrect entry from user"});
   errorCorrelation.addError(Error{10, "Unable to allocate memory!"});

   while (true)
   {
      try
      {
         Error e{errorCorrelation.getError()};
         cout << e << endl;
      }
      catch (const out_of_range &)
      {
         println("Finished processing errors");
         break;
      }
   }
}
