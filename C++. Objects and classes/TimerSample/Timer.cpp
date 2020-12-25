#include "Timer.h"

Timer::Timer()
{
   hours_ = minutes_ = 0;
}

Timer::Timer(const int hours, const int minutes)
{
   hours_ = hours;
   minutes_ = minutes;
}

void Timer::addMinutes(const int minutes)
{
   minutes_ += minutes;
   hours_ += minutes_ / 60;
   minutes_ %= 60;
}

void Timer::addHours(const int hours)
{
   hours_ += hours;
}

void Timer::reset(const int hours, const int minutes)
{
   hours_ = hours;
   minutes_ = minutes;
}

Timer Timer::operator+(const Timer& timer) const
{
   Timer sum;
   sum.minutes_ = minutes_ + timer.minutes_;
   sum.hours_ = hours_ + timer.hours_ + sum.minutes_ / 60;
   sum.minutes_ %= 60;

   return sum;
}

Timer Timer::operator-(const Timer& timer) const
{
   Timer diff_timer;
   const int tot1 = timer.minutes_ + 60 * timer.hours_;
   const int tot2 = minutes_ + 60 * hours_;
   diff_timer.minutes_ = (tot2 - tot1) % 60;
   diff_timer.hours_ = (tot2 - tot1) / 60;

   return diff_timer;
}

Timer Timer::operator*(const double multiplier) const
{
   Timer result;
   const long total_minutes = static_cast<long>(hours_ * multiplier * 60 + minutes_ * multiplier);
   result.hours_ = total_minutes / 60;
   result.minutes_ = total_minutes % 60;

   return result;
}

std::ostream& operator<<(std::ostream& o_stream, const Timer& timer)
{
   o_stream << timer.hours_ << " hours, " << timer.minutes_ << " minutes";
   return o_stream;
}
