export module simulator:bikeSimulator;

export namespace simu
{
   class BikeSimulator
   {
   public:
      [[nodiscard]] BikeSimulator();

      void setOdometer(double miles);
   };
}
