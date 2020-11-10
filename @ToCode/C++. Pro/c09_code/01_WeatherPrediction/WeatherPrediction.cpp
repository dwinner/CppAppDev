#include <iostream>
#include <sstream>

#include "WeatherPrediction.h"

using namespace std;

WeatherPrediction::~WeatherPrediction()
{
}

void WeatherPrediction::setCurrentTempFahrenheit(int inTemp)
{
	mCurrentTempFahrenheit = inTemp;
}

void WeatherPrediction::setPositionOfJupiter(int inDistanceFromMars)
{
	mDistanceFromMars = inDistanceFromMars;
}

int WeatherPrediction::getTomorrowTempFahrenheit() const
{
	// Obviously, this is nonsense
	return (mDistanceFromMars / 1000) + mCurrentTempFahrenheit;
}

double WeatherPrediction::getChanceOfRain() const
{
	// Obviously, this is nonsense too
	return 0.5;
}

void WeatherPrediction::showResult() const
{
	cout << "Result: " << (getChanceOfRain() * 100) << " chance."
		<< " Temp. " << getTomorrowTempFahrenheit() << endl;
}

std::string WeatherPrediction::getTemperature() const
{
	stringstream ss;
	ss << mCurrentTempFahrenheit;
	return ss.str();
}

/*
int main()
{
	WeatherPrediction p;
	p.setCurrentTempFahrenheit(24);
	p.setPositionOfJupiter(80);
	p.showResult();
	return 0;
}
*/