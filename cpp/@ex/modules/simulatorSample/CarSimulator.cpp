module simulator;

import std;

simu::CarSimulator::CarSimulator()
{
   std::println("Car simulator");
}

void simu::CarSimulator::setOdometer(double miles)
{
   double kmValue = ConvertMilesToKm(miles);
   std::println("{}", kmValue);
}
