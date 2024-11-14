#ifndef CAR_ABSTRACTFACTORY_TOYOTAFACTORY_HPP
#define CAR_ABSTRACTFACTORY_TOYOTAFACTORY_HPP

#include "ICarFactory.hpp"
#include "Toyota.hpp"

class ToyotaFactory : public ICarFactory
{
public:
   std::unique_ptr<ICar> makeSuv() override
   {
      return std::make_unique<ToyotaSuv>();
   }

   std::unique_ptr<ICar> makeSedan() override
   {
      return std::make_unique<ToyotaSedan>();
   }
};


#endif //CAR_ABSTRACTFACTORY_TOYOTAFACTORY_HPP
