#include <print>
#include "ICarFactory.hpp"
#include "FordFactory.hpp"
#include "ToyotaFactory.hpp"

using namespace std;

void createSomeCars(ICarFactory &carFactory)
{
   auto sedan{carFactory.makeSedan()};
   auto suv{carFactory.makeSuv()};
   println("Sedan: {}", sedan->info());
   println("SUV: {}", suv->info());
}

int main()
{
   FordFactory fordFactory;
   ToyotaFactory toyotaFactory;
   createSomeCars(fordFactory);
   createSomeCars(toyotaFactory);
}
