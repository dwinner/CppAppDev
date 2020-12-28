#include "LabeledSales.h"
#include <string>

using namespace std;

LabeledSales::NbadIndex::NbadIndex(const string &label,
                                   int badIndexValue,
                                   const string &errorMessage)
    : Sales::BadIndex(badIndexValue, errorMessage)
{
   labelValue_ = label;
}

LabeledSales::LabeledSales(const string &label, int year)
    : Sales(year)
{
   label_ = label;
}

LabeledSales::LabeledSales(const string &label, int year, const double *grosses, int grossCount)
    : Sales(year, grosses, grossCount)
{
   label_ = label;
}

double LabeledSales::operator[](int index) const
{
   if (index < 0 || index >= Months)
   {
      throw NbadIndex(getLabel(), index);
   }

   return Sales::operator[](index);
}

double &LabeledSales::operator[](int index)
{
   if (index < 0 || index >= Months)
   {
      throw NbadIndex(getLabel(), index);
   }

   return Sales::operator[](index);
}
