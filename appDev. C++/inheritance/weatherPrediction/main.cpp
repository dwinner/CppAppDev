#include <iostream>
#include <print>
#include "MyWeatherPrediction.hpp"

using namespace std;

int main()
{
   MyWeatherPrediction prediction;
   prediction.setCurrentTempCelsius(33);
   prediction.setPositionOfJupiter(80);
   prediction.showResult();
   println("{}", prediction.getTemperature());

   return 0;
}
