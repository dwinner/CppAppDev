#include <iostream>

#include "Stock.h"

const int Stks = 4;

int main()
{
   Stock stock;
   stock.acquire("NanoSmart", 20, 12.50);
   stock.show();
   stock.buy(15, 18.25);
   stock.show();
   stock.sell(400, 20.00);
   stock.show();
   std::cin.get();

   Stock fluffyTheCat;
   fluffyTheCat.acquire("NanoSmart", 20, 12.50);
   fluffyTheCat.show();
   fluffyTheCat.buy(15, 18.125);
   fluffyTheCat.show();
   fluffyTheCat.sell(400, 20.00);
   fluffyTheCat.show();
   fluffyTheCat.buy(300000, 40.125);
   fluffyTheCat.show();
   fluffyTheCat.sell(300000, 0.125);
   fluffyTheCat.show();

   {
      // create an array of initialized objects
      Stock stocks[Stks] =
      {
         Stock("NanoSmart", 12, 20.0),
         Stock("Boffo Objects", 200, 2.0),
         Stock("Monolithic Obelisks", 130, 3.25),
         Stock("Fleep Enterprises", 60, 6.5)
      };

      std::cout << "Stock holdings:\n";
      int st;
      for (st = 0; st < Stks; st++)
      {
         stocks[st].show();
      }

      // set pointer to first element
      const Stock* top = &stocks[0];
      for (st = 1; st < Stks; st++)
      {
         top = &top->top_val(stocks[st]);
      }

      // now top points to the most valuable holding
      std::cout << "\nMost valuable holding:\n";
      top->show();
   }

   {
      using std::cout;
      cout << "Using constructors to create new objects\n";
      Stock oneMoreStock("NanoSmart", 12, 20.0); // syntax 1
      oneMoreStock.show();
      Stock stock2 = Stock("Boffo Objects", 2, 2.0); // syntax 2
      stock2.show();

      cout << "Assigning stock1 to stock2:\n";
      stock2 = oneMoreStock;
      cout << "Listing stock1 and stock2:\n";
      oneMoreStock.show();
      stock2.show();

      cout << "Using a constructor to reset an object\n";
      oneMoreStock = Stock("Nifty Foods", 10, 50.0); // temp object
      cout << "Revised stock1:\n";
      oneMoreStock.show();
      cout << "Done\n";
   }

   return 0;
}
