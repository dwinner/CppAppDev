#ifndef CAR_ABSTRACTFACTORY_TOYOTA_HPP
#define CAR_ABSTRACTFACTORY_TOYOTA_HPP

#include <string>
#include "ICar.hpp"

class Toyota : public ICar
{
};

class ToyotaSedan : public Toyota
{
public:
   std::string info() const override
   {
      return "Toyota Sedan";
   }
};

class ToyotaSuv : public Toyota
{
public:
   std::string info() const override
   {
      return "Toyota SUV";
   }
};


#endif //CAR_ABSTRACTFACTORY_TOYOTA_HPP
