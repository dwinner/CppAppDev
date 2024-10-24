import std;
import simulator;

#include "config.h"

using namespace simu;

int main()
{
#ifdef WAY

#if WAY == 1
   #warning "Way is 1"
#elif WAY == 0
   std::println("Ok");
#else
   #error "Way is noway"
#endif

#endif

   CarSimulator carSimu;
   BikeSimulator bikeSimu;

   double miles = 5.6;
   carSimu.setOdometer(miles);
   bikeSimu.setOdometer(miles);

   // n/a: double km = ConvertMilesToKm(miles);

   return 0;
}
