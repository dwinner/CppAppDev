#ifndef CAR_FACTORY_LEASTBUSYFACTORY_HPP
#define CAR_FACTORY_LEASTBUSYFACTORY_HPP

#include <memory>
#include <vector>
#include <stdexcept>
#include "CarFactories.hpp"

class LeastBusyFactory final : public CarFactory
{
public:
   // Constructs an instance, taking ownership of the given factories.
   explicit LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>> factories)
       : factories_{std::move(factories)}
   {
      if (factories_.empty())
      {
         throw std::runtime_error{"No factories provided."};
      }
   }

private:
   std::unique_ptr<ICar> createCar() override
   {
      auto leastBusyFactory{
          std::ranges::min_element(factories_,
                                   [](const auto &factory1, const auto &factory2)
                                   {
                                      return factory1->getNumberOfCarsProduced() < factory2->getNumberOfCarsProduced();
                                   })
      };

      return (*leastBusyFactory)->requestCar();
   }

   std::vector<std::unique_ptr<CarFactory>> factories_;
};


#endif //CAR_FACTORY_LEASTBUSYFACTORY_HPP
