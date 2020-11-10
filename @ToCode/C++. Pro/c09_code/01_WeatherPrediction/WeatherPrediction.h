#pragma once

#include <string>

// Predicts the weather using proven new-age techniques given the current
// temperature and the distance from Jupiter to Mars. If these values are
// not provided, a guess is still given but it's only 99% accurate.
class WeatherPrediction
{
public:
	// Virtual destructor
	virtual ~WeatherPrediction();

	// Sets the current temperature in fahrenheit
	virtual void setCurrentTempFahrenheit(int inTemp);

	// Sets the current distance between Jupiter and Mars
	virtual void setPositionOfJupiter(int inDistanceFromMars);
	
	// Gets the prediction for tomorrow's temperature
	virtual int getTomorrowTempFahrenheit() const;
	
	// Gets the probability of rain tomorrow. 1 means
	// definite rain. 0 means no chance of rain.
	virtual double getChanceOfRain() const;
	
	// Displays the result to the user in this format:
	// Result: x.xx chance. Temp. xx
	virtual void showResult() const;
	
	// Returns string representation of the temperature
	virtual std::string getTemperature() const;

private:
	int mCurrentTempFahrenheit;
	int mDistanceFromMars;
};
