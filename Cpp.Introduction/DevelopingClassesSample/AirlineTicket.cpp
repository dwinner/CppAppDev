#include "stdafx.h";
#include <iostream>
#include "AirlineTicket.h"

using namespace std;

AirlineTicket::AirlineTicket()
{
   hasEliteSuperRewardsStatus = false;
   passengerName = "Unknown Passenger";
   numberOfMiles = 0;
}

AirlineTicket::~AirlineTicket()
{
}

int AirlineTicket::calculatePriceInDollars() const
{
   return getHasEliteSuperRewardsStatus() ? 0 : static_cast<int>(getNumberOfMiles() * 0.1);
}

string AirlineTicket::getPassengerName() const
{
   return passengerName;
}

void AirlineTicket::setPassengerName(string aPassengerName)
{
   passengerName = aPassengerName;
}

int AirlineTicket::getNumberOfMiles() const
{
   return numberOfMiles;
}

void AirlineTicket::setNumberOfMiles(int miles)
{
   numberOfMiles = miles;
}

bool AirlineTicket::getHasEliteSuperRewardsStatus() const
{
   return hasEliteSuperRewardsStatus;
}

void AirlineTicket::setHasEliteSuperRewardsStatus(bool aStatus)
{
   hasEliteSuperRewardsStatus = aStatus;
}

