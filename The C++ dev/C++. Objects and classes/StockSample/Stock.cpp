#include "Stock.h"

#include <iostream>

Stock::Stock()
{
   std::cout << "Default constructor called\n";
   company_ = "no name";
   shares_ = 0;
   shareVal_ = 0.0;
   totalVal_ = 0.0;
}

Stock::Stock(const std::string& co, long n, double pr)
{
   std::cout << "Constructor using " << co << " called\n";

   company_ = co;
   if (n < 0)
   {
      std::cout << "Number of shares can't be negative; " << company_ << " shares set to 0.\n";
      shares_ = 0;
   }
   else
   {
      shares_ = n;
   }

   shareVal_ = pr;
   set_total();
}

Stock::~Stock()
{
   std::cout << "Bye, " << company_ << "!\n";
}

void Stock::acquire(const std::string& co, long n, double pr)
{
   company_ = co;
   if (n < 0)
   {
      std::cout << "Number of shares can't be negative; " << company_ << " shares set to 0.\n";
      shares_ = 0;
   }
   else
   {
      shares_ = n;
   }

   shareVal_ = pr;
   set_total();
}

void Stock::buy(long num, double price)
{
   if (num < 0)
   {
      std::cerr << "Number of shares purchased can't be negative. Transaction is aborted.\n";
   }
   else
   {
      shares_ += num;
      shareVal_ = price;
      set_total();
   }
}

void Stock::sell(long num, double price)
{
   using std::cerr;

   if (num < 0)
   {
      cerr << "Number of shares sold can't be negative. Transaction is aborted.\n";
   }
   else if (num > shares_)
   {
      cerr << "You can't sell more than you have! Transaction is aborted.\n";
   }
   else
   {
      shares_ -= num;
      shareVal_ = price;
      set_total();
   }
}

void Stock::update(double price)
{
   shareVal_ = price;
   set_total();
}

void Stock::show() const
{
   using std::cout;
   using std::ios_base;

   // set format to #.###
   ios_base::fmtflags orig = cout.setf(ios_base::fixed);
   int prec = static_cast<int>(cout.precision(3));

   cout << "Company: " << company_ << "  Shares: " << shares_ << '\n';
   cout << "  Share Price: $" << shareVal_;

   // set format to *.**
   cout.precision(2);
   cout << "  Total Worth: $" << totalVal_ << '\n';

   // restore original format
   cout.setf(orig, ios_base::floatfield);
   cout.precision(prec);
}

const Stock& Stock::top_val(const Stock& aStock) const
{   
   return aStock.totalVal_ > totalVal_ ? aStock : *this;
}
