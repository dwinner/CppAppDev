/**
 * Using the Tv and Remote classes
 */

#include <iostream>
#include "Tv.h"
#include "Remote.h"

int main()
{
   using std::cout;
   Tv s42;
   cout << "Initial settings for 42\" TV:\n";
   s42.settings();
   s42.onOff();
   s42.channelUp();
   cout << "\nAdjusted settings for 42\" TV:\n";
   s42.settings();

   Remote grey;

   grey.setChannel(s42, 10);
   grey.volumeUp(s42);
   grey.volumeUp(s42);
   cout << "\n42\" settings after using remote:\n";
   s42.settings();

   Tv s58(Tv::On);
   s58.setMode();
   grey.setChannel(s58, 28);
   cout << "\n58\" settings:\n";
   s58.settings();

   return 0;
}
