#pragma once

#include <string>
#include <optional>

class AirlineTicket
{
public:
   AirlineTicket(
       std::string passengerName,
       int numberOfMiles,
       bool hasEliteSuperRewardsStatus,
       int8_t frequentFlyerNum);

   AirlineTicket();

   double calculatePriceInDollars() const;

   inline std::string getPassengerName();

   void setPassengerName(std::string name);

   inline int getNumberOfMiles() const;

   void setNumberOfMiles(int miles);

   inline bool hasEliteSuperRewardsStatus() const;

   void setHasEliteSuperRewardsStatus(bool status);

   inline int8_t getFrequentNum();

   void setFrequentNum(int8_t frequentNum);

private:
   static inline constexpr double DefaultQuota = 1E-1;

   std::string _passengerName{"Unknown Passenger"};
   int _numberOfMiles{0};
   bool _hasEliteSuperRewardsStatus{false};
   std::optional<int8_t> _frequentFlyerNum{};
};
