module simulator;

import std;

simu::BikeSimulator::BikeSimulator()
{
   std::println("Bike simulator");
}

void simu::BikeSimulator::setOdometer(double miles)
{
   double kmValue = ConvertMilesToKm(miles);
   std::println("{}", kmValue);
}
