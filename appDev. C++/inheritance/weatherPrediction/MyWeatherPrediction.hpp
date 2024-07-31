#ifndef WEATHERPREDICTION_MYWEATHERPREDICTION_HPP
#define WEATHERPREDICTION_MYWEATHERPREDICTION_HPP


#include <string>
#include "WeatherPrediction.hpp"


class MyWeatherPrediction : public WeatherPrediction
{
public:
   virtual void setCurrentTempCelsius(int temp);

   virtual int getTomorrowTempCelsius() const;

   void showResult() const override;

   std::string getTemperature() const override;

private:
   static int convertCelsiusToFahrenheit(int celsius);

   static int convertFahrenheitToCelsius(int fahrenheit);
};


#endif //WEATHERPREDICTION_MYWEATHERPREDICTION_HPP
