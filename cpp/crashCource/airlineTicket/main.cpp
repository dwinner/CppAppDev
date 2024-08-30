#include <iostream>
#include "AirlineTicket.h"

constexpr const int miles = 700;
using namespace std;

auto main() -> int
{
   AirlineTicket myTicket;  // Stack-based AirlineTicket
   myTicket.setPassengerName("Sherman T. Socketwrench");
   myTicket.setNumberOfMiles(miles);
   double cost{myTicket.calculatePriceInDollars()};
   cout << "This ticket will cost $" << cost << endl;

   return 0;
}
