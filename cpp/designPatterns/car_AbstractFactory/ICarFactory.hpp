#ifndef CAR_ABSTRACTFACTORY_ICARFACTORY_HPP
#define CAR_ABSTRACTFACTORY_ICARFACTORY_HPP

#include <memory>
#include "ICar.hpp"

class ICarFactory
{
public:
   virtual ~ICarFactory() = default;  // Always a virtual destructor!

   virtual std::unique_ptr<ICar> makeSuv() = 0;

   virtual std::unique_ptr<ICar> makeSedan() = 0;
};


#endif //CAR_ABSTRACTFACTORY_ICARFACTORY_HPP
