#include "Stone.h"

#include <iostream>

namespace stone_sample
{
   using namespace std;

   Stone::Stone(double lbs)
   {
      stone_ = static_cast<int>(lbs) / lbs_per_stn;
      pdsLeft_ = static_cast<int>(lbs) % lbs_per_stn + lbs - static_cast<int>(lbs);
      pounds_ = lbs;
   }

   Stone::Stone(int stn, double lbs)
   {
      stone_ = stn;
      pdsLeft_ = lbs;
      pounds_ = stn * lbs_per_stn + lbs;
   }

   Stone::Stone()
      : stone_(0), pdsLeft_(.0), pounds_(.0)
   {
   }

   void Stone::show_lbs() const
   {
      cout << pounds_ << " pounds\n";
   }

   void Stone::show_stn() const
   {
      std::cout << stone_ << " stone, " << pdsLeft_ << " pounds\n";
   }

   Stone::operator int() const
   {
      return static_cast<int>(pounds_ + 0.5);
   }

   Stone::operator double() const
   {
      return pounds_;
   }
}
