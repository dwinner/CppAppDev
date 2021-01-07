#include "Sales.h"

using std::string;

Sales::BadIndex::BadIndex(int index, const string &errorMessage)
    : std::logic_error(errorMessage),
      badIndexValue_(index)
{
}

Sales::Sales(int year)
{
   year_ = year;
   for (int i = 0; i < Months; ++i)
   {
      gross_[i] = 0;
   }
}

Sales::Sales(int year, const double *gross, int grossCount)
{
   year_ = year;
   int lim = (grossCount < Months) ? grossCount : Months;
   int i;
   for (i = 0; i < lim; ++i)
   {
      gross_[i] = gross[i];
   }
   // for i > n and i < MONTHS
   for (; i < Months; ++i)
   {
      gross_[i] = 0;
   }
}

double Sales::operator[](int index) const
{
   if (index < 0 || index >= Months)
   {
      throw BadIndex(index);
   }

   return gross_[index];
}

double &Sales::operator[](int index)
{
   if (index < 0 || index >= Months)
   {
      throw BadIndex(index);
   }

   return gross_[index];
}
