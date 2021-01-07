#ifndef NESTED_EXCEPTIONS_SALES_H
#define NESTED_EXCEPTIONS_SALES_H

#include <stdexcept>
#include <string>


class Sales
{
public:
   enum
   {
      Months = 12
   };   // could be a static const

   class BadIndex : public std::logic_error
   {
   public:
      explicit BadIndex(int index, const std::string &errorMessage = "Index error in Sales object\n");

      int getBadIndex() const
      {
         return badIndexValue_;
      }

      virtual ~BadIndex() noexcept
      {
      }

   private:
      int badIndexValue_;  // bad index value
   };

   explicit Sales(int year = 0);

   Sales(int year, const double *gross, int grossCount);

   virtual ~Sales()
   {
   }

   int getYear() const
   {
      return year_;
   }

   virtual double operator[](int index) const;

   virtual double &operator[](int index);

private:
   double gross_[Months];
   int year_;
};


#endif //NESTED_EXCEPTIONS_SALES_H
