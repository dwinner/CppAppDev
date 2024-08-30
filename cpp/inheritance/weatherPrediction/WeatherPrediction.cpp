#include <print>
#include <string>
#include "WeatherPrediction.hpp"

using namespace std;

WeatherPrediction::~WeatherPrediction()
{
}

void WeatherPrediction::setCurrentTempFahrenheit(int temp)
{
   _currentTempFahrenheit = temp;
}

void WeatherPrediction::setPositionOfJupiter(int distanceFromMars)
{
   _distanceFromMars = distanceFromMars;
}

int WeatherPrediction::getTomorrowTempFahrenheit() const
{
   // Obviously, this is nonsense
   return (_distanceFromMars / 1000) + _currentTempFahrenheit;
}

double WeatherPrediction::getChanceOfRain() const
{
   // Obviously, this is nonsense too
   return 0.5;
}

void WeatherPrediction::showResult() const
{
   println("Result: {} chance.  Temp. {}",
           getChanceOfRain() * 100, getTomorrowTempFahrenheit());
}

std::string WeatherPrediction::getTemperature() const
{
   return to_string(_currentTempFahrenheit);
}
