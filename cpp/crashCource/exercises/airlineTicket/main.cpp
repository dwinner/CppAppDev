#include <print>
#include "AirlineTicket.h"

constexpr const int miles = 700;
using namespace std;

auto main() -> int
{
   AirlineTicket myTicket;  // Stack-based AirlineTicket

   myTicket.setPassengerName("Sherman T. Socketwrench");
   myTicket.setNumberOfMiles(miles);
   myTicket.setFrequentNum(5);

   double cost{myTicket.calculatePriceInDollars()};

   println("This ticket will cost $ {}", cost);

   return 0;
}
