#include <vector>
#include <print>
#include "CarFactories.hpp"
#include "LeastBusyFactory.hpp"

using namespace std;

int main()
{
   ToyotaFactory myFactory;
   auto myCar{myFactory.requestCar()};
   println("{}", myCar->info());    // Outputs Toyota
   println("------------");

   vector<unique_ptr<CarFactory>> factories;

   // Create 3 Ford factories and 1 Toyota factory.
   factories.push_back(make_unique<FordFactory>());
   factories.push_back(make_unique<FordFactory>());
   factories.push_back(make_unique<FordFactory>());
   factories.push_back(make_unique<ToyotaFactory>());

   // To get more interesting results, preorder some cars from specific factories.
   for (size_t i: {0, 0, 0, 1, 1, 2})
   {
      factories[i]->requestCar();
   }

   // Create a factory that automatically selects the least busy
   // factory from a list of given factories.
   LeastBusyFactory leastBusyFactory{std::move(factories)};

   // Build 10 cars from the least busy factory.
   for (unsigned i{0}; i < 10; ++i)
   {
      auto theCar{leastBusyFactory.requestCar()};
      println("{}", theCar->info());
   }
}
