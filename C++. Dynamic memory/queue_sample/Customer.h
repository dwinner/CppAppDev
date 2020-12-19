#ifndef QUEUE_SAMPLE_CUSTOMER_H
#define QUEUE_SAMPLE_CUSTOMER_H

class Customer
{
public:
   Customer()
      : arrive(0), processtime(0)
   {
   }

   void set(long when);

   long when() const
   {
      return arrive;
   }

   int ptime() const
   {
      return processtime;
   }

private:
   long arrive;        // arrival time for customer
   int processtime;    // processing time for customer
};

#endif //QUEUE_SAMPLE_CUSTOMER_H
