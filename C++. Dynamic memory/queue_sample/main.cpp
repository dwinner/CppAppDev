#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Queue.h"

const int min_per_hr = 60;

bool newcustomer(double x); // is there a new customer?

int main()
{
   using std::cin;
   using std::cout;
   using std::endl;
   using std::ios_base;

   // setting things up
   std::srand(std::time(nullptr)); //  random initializing of rand()

   cout << "Case Study: Bank of Heather Automatic Teller\n";
   cout << "Enter maximum size of queue: ";
   int qs;
   cin >> qs;
   Queue line(qs); // line queue holds up to qs people

   cout << "Enter the number of simulation hours: ";
   int hours; //  hours of simulation
   cin >> hours;
   // simulation will run 1 cycle per minute
   const long cyclelimit = min_per_hr * hours; // # of cycles

   cout << "Enter the average number of customers per hour: ";
   double perhour; //  average # of arrival per hour
   cin >> perhour;
   const double min_per_cust = min_per_hr / perhour;

   item temp; //  new customer data
   long turnaways = 0; //  turned away by full queue
   long customers = 0; //  joined the queue
   long served = 0; //  served during the simulation
   long sum_line = 0; //  cumulative line length
   int wait_time = 0; //  time until autoteller is free
   long line_wait = 0; //  cumulative time in line

   // running the simulation
   for (auto cycle = 0; cycle < cyclelimit; cycle++)
   {
      if (newcustomer(min_per_cust)) // have newcomer
      {
         if (line.isFull())
         {
            turnaways++;
         }
         else
         {
            customers++;
            temp.set(cycle); // cycle = time of arrival
            line.enQueue(temp); // add newcomer to line
         }
      }

      if (wait_time <= 0 && !line.isEmpty())
      {
         line.deQueue(temp); // attend next customer
         wait_time = temp.ptime(); // for wait_time minutes
         line_wait += cycle - temp.when();
         served++;
      }

      if (wait_time > 0)
      {
         wait_time--;
      }

      sum_line += line.queueCount();
   }

   // reporting results
   if (customers > 0)
   {
      cout << "customers accepted: " << customers << endl;
      cout << "  customers served: " << served << endl;
      cout << "         turnaways: " << turnaways << endl;
      cout << "average queue size: ";
      cout.precision(2);
      cout.setf(ios_base::fixed, ios_base::floatfield);
      cout << static_cast<double>(sum_line) / cyclelimit << endl;
      cout << " average wait time: " << static_cast<double>(line_wait) / served << " minutes\n";
   }
   else
   {
      cout << "No customers!\n";
   }

   cout << "Done!\n";

   return 0;
}

//  x = average time, in minutes, between customers
//  return value is true if customer shows up this minute
bool newcustomer(double x)
{
   return std::rand() * x / RAND_MAX < 1;
}
