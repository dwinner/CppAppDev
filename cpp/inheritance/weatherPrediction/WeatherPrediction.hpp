#ifndef WEATHERPREDICTION_WEATHERPREDICTION_HPP
#define WEATHERPREDICTION_WEATHERPREDICTION_HPP

/**
 * @brief Predicts the weather using proven new-age techniques given the current
 *  temperature and the distance from Jupiter to Mars. If these values are
 *  not provided, a guess is still given but it's only 99% accurate.
 */
class WeatherPrediction
{
public:
   /**
    * @brief Virtual destructor
    */
   virtual ~WeatherPrediction();

   /**
    * @brief Sets the current temperature in Fahrenheit
    * @param temp temperature in Fahrenheit
    */
   virtual void setCurrentTempFahrenheit(int temp);

   /**
    * @brief Sets the current distance between Jupiter and Mars
    * @param distanceFromMars distance between Jupiter and Mars
    */
   virtual void setPositionOfJupiter(int distanceFromMars);

   /**
    * @brief Gets the prediction for tomorrow's temperature
    * @return prediction for tomorrow's temperature
    */
   virtual int getTomorrowTempFahrenheit() const;

   /**
    * @brief Gets the probability of rain tomorrow.
    * @details 1 means definite rain. 0 means no chance of rain.
    * @return the probability of rain tomorrow.
    */
   virtual double getChanceOfRain() const;

   /**
    * @brief Displays the result to the user in this format: Result: x.xx chance. Temp. xx
    */
   virtual void showResult() const;

   /**
    * Returns a string representation of the temperature
    * @return string representation of the temperature
    */
   virtual std::string getTemperature() const;

private:
   int _currentTempFahrenheit{0};
   int _distanceFromMars{0};
};


#endif //WEATHERPREDICTION_WEATHERPREDICTION_HPP
