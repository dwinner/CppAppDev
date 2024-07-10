#include "AirlineTicket.h"

#include <utility>

using namespace std;

double AirlineTicket::calculatePriceInDollars() const
{
   if (hasEliteSuperRewardsStatus())
   {
      // Elite Super Rewards customers fly for free!
      return 0;
   }

   // The cost of the ticket is the number of miles times 0.1.
   // Real airlines probably have a more complicated formula!
   return getNumberOfMiles() * 0.1;
}

[[maybe_unused]] string AirlineTicket::getPassengerName()
{
   return _passengerName;
}

void AirlineTicket::setPassengerName(string name)
{
   _passengerName = std::move(name);
}

int AirlineTicket::getNumberOfMiles() const
{
   return _numberOfMiles;
}

void AirlineTicket::setNumberOfMiles(int miles)
{
   _numberOfMiles = miles;
}

bool AirlineTicket::hasEliteSuperRewardsStatus() const
{
   return _hasEliteSuperRewardsStatus;
}

[[maybe_unused]] void AirlineTicket::setHasEliteSuperRewardsStatus(bool status)
{
   _hasEliteSuperRewardsStatus = status;
}
