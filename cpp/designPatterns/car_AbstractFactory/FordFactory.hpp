#ifndef CAR_ABSTRACTFACTORY_FORDFACTORY_HPP
#define CAR_ABSTRACTFACTORY_FORDFACTORY_HPP

#include <memory>
#include "ICarFactory.hpp"
#include "Ford.hpp"

class FordFactory : public ICarFactory
{
public:
   std::unique_ptr<ICar> makeSuv() override
   {
      return std::make_unique<FordSuv>();
   }

   std::unique_ptr<ICar> makeSedan() override
   {
      return std::make_unique<FordSedan>();
   }
};


#endif //CAR_ABSTRACTFACTORY_FORDFACTORY_HPP
