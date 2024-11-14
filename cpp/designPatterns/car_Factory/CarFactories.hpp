#ifndef CAR_FACTORY_CARFACTORIES_HPP
#define CAR_FACTORY_CARFACTORIES_HPP

#include <memory>
#include "Cars.hpp"

class CarFactory
{
public:
   virtual ~CarFactory() = default;  // Always a virtual destructor!

   CarFactory() = default;

   CarFactory(const CarFactory &) = default;

   CarFactory &operator=(const CarFactory &) = default;

   CarFactory(CarFactory &&) = default;

   CarFactory &operator=(CarFactory &&) = default;

   std::unique_ptr<ICar> requestCar()
   {
      // Increment the number of cars produced and return the new car.
      ++numOfCarsProduced_;
      return createCar();
   }

   unsigned getNumberOfCarsProduced() const
   {
      return numOfCarsProduced_;
   }

private:
   virtual std::unique_ptr<ICar> createCar() = 0;

   unsigned numOfCarsProduced_{0};
};

class FordFactory final : public CarFactory
{
private:
   std::unique_ptr<ICar> createCar() override
   {
      return std::make_unique<Ford>();
   }
};

class ToyotaFactory final : public CarFactory
{
private:
   std::unique_ptr<ICar> createCar() override
   {
      return std::make_unique<Toyota>();
   }
};


#endif //CAR_FACTORY_CARFACTORIES_HPP
