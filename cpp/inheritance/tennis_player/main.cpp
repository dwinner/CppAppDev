#include <iostream>
#include "TableTennisPlayer.h"
#include "RatedPlayer.h"

int main()
{
   using std::cout;
   using std::endl;

   TableTennisPlayer player1("Tara", "Boomdea", false);
   RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
   rplayer1.getName(); // derived object uses base method

   if (rplayer1.getRating())
   {
      cout << ": has a table.\n";
   }
   else
   {
      cout << ": hasn't a table.\n";
   }

   player1.getName(); // base object uses base method

   if (player1.hasTable())
   {
      cout << ": has a table";
   }
   else
   {
      cout << ": hasn't a table.\n";
   }

   cout << "Name: ";
   rplayer1.getName();
   cout << "; Rating: " << rplayer1.getRating() << endl;

   // initialize RatedPlayer using TableTennisPlayer object
   RatedPlayer rplayer2(1212, player1);
   cout << "Name: ";
   rplayer2.getName();
   cout << "; Rating: " << rplayer2.getRating() << endl;

   return 0;
}
