#ifndef CAR_ABSTRACTFACTORY_ICAR_HPP
#define CAR_ABSTRACTFACTORY_ICAR_HPP

#include <string>

class ICar
{
public:
   virtual ~ICar() = default;  // Always a virtual destructor!

   virtual std::string info() const = 0;
};


#endif //CAR_ABSTRACTFACTORY_ICAR_HPP
