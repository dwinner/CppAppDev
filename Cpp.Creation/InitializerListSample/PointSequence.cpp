#include "stdafx.h"
#include "PointSequence.h"
#include <ostream>
#include <iostream>

PointSequence::PointSequence(std::initializer_list<double> args)
{
   if (args.size() % 2 != 0)
   {
      throw std::invalid_argument("initializer_list should contain even number of elements.");
   }

   for (auto iter = args.begin(); iter != args.end(); ++iter)
   {
      points.push_back(*iter);
   }
}

void PointSequence::dumpPoints() const
{
   for (auto iter = points.cbegin(); iter != points.cend(); iter += 2)
   {
      std::cout << "(" << *iter << ", " << *(iter + 1) << ")" << std::endl;
   }
}
