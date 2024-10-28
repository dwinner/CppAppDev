export module simulator:carSimulator;

export namespace simu
{
   class CarSimulator
   {
   public:
      [[nodiscard]] CarSimulator();

      void setOdometer(double miles);
   };
}
