#pragma once
#include <string>

/**
 * Stock class
 */
class Stock
{
public:
   Stock();
   Stock(const std::string& co, long n = 0, double pr = 0.0);
   ~Stock();
   void acquire(const std::string& co, long n, double pr);
   void buy(long num, double price);
   void sell(long num, double price);
   void update(double price);
   void show() const;
   const Stock& top_val(const Stock& aStock) const;

private:
   std::string company_;
   long shares_;
   double shareVal_;
   double totalVal_{};

   void set_total()
   {
      totalVal_ = shares_ * shareVal_;
   }
};
