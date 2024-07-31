#ifndef MILESESTIMATOR_EFFICIENTCARMILESESTIMATOR_HPP
#define MILESESTIMATOR_EFFICIENTCARMILESESTIMATOR_HPP

#include "MilesEstimator.hpp"

class EfficientCarMilesEstimator : public MilesEstimator
{
private:
   int getMilesPerGallon() const override
   {
      return 35;
   }
};


#endif //MILESESTIMATOR_EFFICIENTCARMILESESTIMATOR_HPP
