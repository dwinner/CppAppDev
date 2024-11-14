#ifndef CAR_ABSTRACTFACTORY_FORD_HPP
#define CAR_ABSTRACTFACTORY_FORD_HPP

#include <string>
#include "ICar.hpp"

class Ford : public ICar
{
};

class FordSedan : public Ford
{
public:
   std::string info() const override
   {
      return "Ford Sedan";
   }
};

class FordSuv : public Ford
{
public:
   std::string info() const override
   {
      return "Ford SUV";
   }
};


#endif //CAR_ABSTRACTFACTORY_FORD_HPP
