#pragma once

namespace stone_sample
{
   class Stone
   {
   public:
      /**
       * \brief Construct from double pounds
       * \param lbs double pounds
       */
      Stone(double lbs);

      /**
       * \brief Construct from stone, lbs
       * \param stn count of stones
       * \param lbs pounds in double
       */
      Stone(int stn, double lbs);

      /**
       * \brief Default constructor
       */
      Stone();

      ~Stone() = default;

      /**
       * \brief Show weight in pounds format
       */
      void show_lbs() const;

      /**
       * \brief Show weight in stone format
       */
      void show_stn() const;

      // conversion functions
      operator int() const;

      operator double() const;

   private:
      enum { lbs_per_stn = 14 }; // pounds per stone
      int stone_; // whole stones
      double pdsLeft_; // fractional pounds
      double pounds_; // entire weight in pounds
   };
}
