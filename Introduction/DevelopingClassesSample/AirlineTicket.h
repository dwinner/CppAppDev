#pragma once

using namespace std;
#include <string>

class AirlineTicket
{
public:
   AirlineTicket();
   ~AirlineTicket();
   int calculatePriceInDollars() const;
   string getPassengerName() const;
   void setPassengerName(std::string aPassengerName);
   int getNumberOfMiles() const;
   void setNumberOfMiles(int miles);
   bool getHasEliteSuperRewardsStatus() const;
   void setHasEliteSuperRewardsStatus(bool aStatus);
protected:
   string passengerName;
   int numberOfMiles;
   bool hasEliteSuperRewardsStatus;
};