#ifndef AIRLINETICKET_AIRLINETICKET_H
#define AIRLINETICKET_AIRLINETICKET_H

#include <string>

class AirlineTicket
{
public:
   [[nodiscard]] double calculatePriceInDollars() const;

   [[maybe_unused]] std::string getPassengerName();

   void setPassengerName(std::string name);

   [[nodiscard]] int getNumberOfMiles() const;

   void setNumberOfMiles(int miles);

   [[nodiscard]] bool hasEliteSuperRewardsStatus() const;

   [[maybe_unused]] void setHasEliteSuperRewardsStatus(bool status);

private:
   std::string _passengerName{"Unknown Passenger"};
   int _numberOfMiles{0};
   bool _hasEliteSuperRewardsStatus{false};
};

#endif //AIRLINETICKET_AIRLINETICKET_H
