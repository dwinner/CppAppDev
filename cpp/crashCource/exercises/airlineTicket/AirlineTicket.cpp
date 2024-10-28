#include "AirlineTicket.h"

#include <utility>

using namespace std;

AirlineTicket::AirlineTicket(
    string passengerName,
    int numberOfMiles,
    bool hasEliteSuperRewardsStatus,
    int8_t frequentFlyerNum) :
    _passengerName(std::move(passengerName)),
    _numberOfMiles(numberOfMiles),
    _hasEliteSuperRewardsStatus(hasEliteSuperRewardsStatus),
    _frequentFlyerNum(frequentFlyerNum)
{}

AirlineTicket::AirlineTicket() = default;

double AirlineTicket::calculatePriceInDollars() const
{
   if (hasEliteSuperRewardsStatus())
   {
      // Elite Super Rewards customers fly for free!
      return 0;
   }

   // The cost of the ticket is the number of miles times 0.1.
   // Real airlines probably have a more complicated formula!
   return getNumberOfMiles() * DefaultQuota;
}

inline string AirlineTicket::getPassengerName()
{
   return _passengerName;
}

void AirlineTicket::setPassengerName(string name)
{
   _passengerName = std::move(name);
}

inline int AirlineTicket::getNumberOfMiles() const
{
   return _numberOfMiles;
}

void AirlineTicket::setNumberOfMiles(int miles)
{
   _numberOfMiles = miles;
}

inline bool AirlineTicket::hasEliteSuperRewardsStatus() const
{
   return _hasEliteSuperRewardsStatus;
}

void AirlineTicket::setHasEliteSuperRewardsStatus(bool status)
{
   _hasEliteSuperRewardsStatus = status;
}

inline int8_t AirlineTicket::getFrequentNum()
{
   return _frequentFlyerNum.value_or(0);
}

void AirlineTicket::setFrequentNum(int8_t frequentNum)
{
   _frequentFlyerNum = frequentNum;
}
