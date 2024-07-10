/**
 * Testing the Queue
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "queue_iface.h"

#define MIN_PER_HR   60.0

/**
 * \brief Finds out if a new customer is there
 * \param x Average time, in minutes, between customers
 * \return return value is true if customer shows up this minute
 */
bool newCustomer(double x);

/**
 * \brief Set customer's parameters
 * \details When is the time at which the customer arrives
 *          function returns an Item structure with the arrival time
 *          set to when and the processing time set to a random value
 *          in the range 1 - 3
 * \param when When a new customer came
 * \return New queue item
 */
Item customerTime(long when);

int main()
{
   Queue line; /* new customer data */
   Item temp; /* hours of simulation */
   int hours; /* hours of simulation */
   int perhour; /* average # of arrivals per hour */
   long cycle, cyclelimit; /* loop counter, limit */
   long turnaways = 0; /* turned away by full queue */
   long customers = 0; /* joined the queue */
   long served = 0; /* served during the simulation */
   long sum_line = 0; /* cumulative line length */
   int wait_time = 0; /* time until Sigmund is free */
   double min_per_cust; /* average time between arrivals */
   long line_wait = 0; /* cumulative time in line */

   initializeQueue(&line);
   srand(time(0));
   puts("Case Study: Sigmund Lander's Advice Booth");
   puts("Enter the number of simulation hours:");
   scanf_s("%d", &hours);
   cyclelimit = MIN_PER_HR * hours;
   puts("Enter the average number of customers per hour:");
   scanf_s("%d", &perhour);
   min_per_cust = MIN_PER_HR / perhour;

   for (cycle = 0; cycle < cyclelimit; cycle++)
   {
      if (newCustomer(min_per_cust))
      {
         if (queueIsFull(&line))
         {
            turnaways++;
         }
         else
         {
            customers++;
            temp = customerTime(cycle);
            enqueue(temp, &line);
         }
      }

      if (wait_time <= 0 && !queueIsEmpty(&line))
      {
         dequeue(&temp, &line);
         wait_time = temp.processTime;
         line_wait += cycle - temp.arrive;
         served++;
      }

      if (wait_time > 0)
      {
         wait_time--;
      }

      sum_line += queueItemCount(&line);
   }

   if (customers > 0)
   {
      printf("customers accepted: %ld\n", customers);
      printf("  customers served: %ld\n", served);
      printf("       turnaways: %ld\n", turnaways);
      printf("average queue size: %.2f\n",
             (double)sum_line / cyclelimit);
      printf(" average wait time: %.2f minutes\n",
             (double)line_wait / served);
   }
   else
   {
      puts("No customers!");
   }

   cleanQueue(&line);
   puts("Bye!");

   return EXIT_SUCCESS;
}

bool newCustomer(const double x)
{
   return rand() * x / RAND_MAX < 1/* ? true : false*/;
}

Item customerTime(const long when)
{
   Item cust;

   cust.processTime = rand() % 3 + 1;
   cust.arrive = when;

   return cust;
}
