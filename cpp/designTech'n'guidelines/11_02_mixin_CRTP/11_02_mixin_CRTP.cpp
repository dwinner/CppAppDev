import std;

using namespace std;

template <typename TDerived>
class SelfDrivable
{
public:
   void drive()
   {
      auto& self{static_cast<TDerived&>(*this)};
      self.setSpeed(1.2);
   }
};

class Car : public SelfDrivable<Car>
{
public:
   void setSpeed(double speed)
   {
      println("Car speed set to {}.", speed);
   }
};

class Truck : public SelfDrivable<Truck>
{
public:
   void setSpeed(double speed)
   {
      println("Truck speed set to {}.", speed);
   }
};

int main()
{
   Car car;
   Truck truck;
   car.drive();
   truck.drive();
}
