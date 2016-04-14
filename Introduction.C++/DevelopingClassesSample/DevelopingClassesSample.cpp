// DevelopingClassesSample.cpp: Пример разработки классов.

#include "stdafx.h"
#include <memory>
#include "AirlineTicket.h";
#include <iostream>

using namespace std;

int main()
{
   AirlineTicket stackBasedTicket;

   stackBasedTicket.setPassengerName("Sherman T. Socketwrench");
   stackBasedTicket.setNumberOfMiles(700);
   int cost = stackBasedTicket.calculatePriceInDollars();
   cout << "This ticket will cost $" << cost << endl;

   shared_ptr<AirlineTicket> heapBasedTicket(new AirlineTicket());
   heapBasedTicket->setPassengerName("Laudimore M. Hallidue");
   heapBasedTicket->setNumberOfMiles(2000);
   heapBasedTicket->setHasEliteSuperRewardsStatus(true);
   int cost2 = heapBasedTicket->calculatePriceInDollars();
   cout << "This other ticket will cost $" << cost2 << endl;

   AirlineTicket* rawHeapBasedTicket = new AirlineTicket;
   delete rawHeapBasedTicket;

   return 0;
}

