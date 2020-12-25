#pragma once
#include <ostream>

class Timer
{
public:
   Timer();

   explicit Timer(int hours, int minutes = 0);

   void addMinutes(int minutes);

   void addHours(int hours);

   void reset(int hours = 0, int minutes = 0);

   Timer operator+(const Timer& timer) const;

   Timer operator-(const Timer& timer) const;

   Timer operator*(double multiplier) const;

   friend Timer operator*(const double minutes, const Timer& timer)
   {
      return timer * minutes;
   }

   friend std::ostream& operator<<(std::ostream& o_stream, const Timer& timer);

private:
   int hours_;
   int minutes_;
};
