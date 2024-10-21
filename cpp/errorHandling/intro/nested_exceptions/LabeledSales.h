#ifndef NESTED_EXCEPTIONS_LABELEDSALES_H
#define NESTED_EXCEPTIONS_LABELEDSALES_H

#include "Sales.h"
#include <string>

class LabeledSales : public Sales
{
public:
   class NbadIndex : public Sales::BadIndex
   {
   public:
      NbadIndex(const std::string &label,
                int badIndexValue,
                const std::string &errorMessage = "Index error in LabeledSales object\n");

      const std::string &getLabelValue() const
      {
         return labelValue_;
      }

      virtual ~NbadIndex() throw()
      {
      }

   private:
      std::string labelValue_;
   };

   explicit LabeledSales(const std::string &label = "none", int year = 0);

   LabeledSales(const std::string &label, int year, const double *grosses, int grossCount);

   virtual ~LabeledSales()
   {
   }

   const std::string &getLabel() const
   {
      return label_;
   }

   virtual double operator[](int index) const;

   virtual double &operator[](int index);

private:
   std::string label_;
};


#endif //NESTED_EXCEPTIONS_LABELEDSALES_H
