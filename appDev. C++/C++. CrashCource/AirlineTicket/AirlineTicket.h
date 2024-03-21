#ifndef AIRLINETICKET_AIRLINETICKET_H
#define AIRLINETICKET_AIRLINETICKET_H

#include <string>

class AirlineTicket
{
public:
   double calculatePriceInDollars();

   std::string getPassengerName();

   void setPassengerName(std::string name);

   int getNumberOfMiles();

   void setNumberOfMiles(int miles);

   bool hasEliteSuperRewardsStatus();

   void setHasEliteSuperRewardsStatus(bool status);

private:
   std::string m_passengerName{"Unknown Passenger"};
   int m_numberOfMiles{0};
   bool m_hasEliteSuperRewardsStatus{false};
};

#endif //AIRLINETICKET_AIRLINETICKET_H
