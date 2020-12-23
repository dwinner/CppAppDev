#include <iostream>
#include <string>
#include "AccountBase.h"
#include "Brass.h"
#include "BrassPlus.h"

const int Clients = 4;

int main()
{
   using std::cin;
   using std::cout;
   using std::endl;

   AccountBase* p_clients[Clients];
   std::string temp;
   long tempnum;
   double tempbal;
   char kind;

   for (int i = 0; i < Clients; i++)
   {
      cout << "Enter client's name: ";
      getline(cin, temp);
      cout << "Enter client's account number: ";
      cin >> tempnum;
      cout << "Enter opening balance: $";
      cin >> tempbal;
      cout << "Enter 1 for Brass Account or 2 for BrassPlus Account: ";

      while (cin >> kind && (kind != '1' && kind != '2'))
      {
         cout << "Enter either 1 or 2: ";
      }

      if (kind == '1')
      {
         p_clients[i] = new Brass(temp, tempnum, tempbal);
      }
      else
      {
         double tmax, trate;
         cout << "Enter the overdraft limit: $";
         cin >> tmax;
         cout << "Enter the interest rate "
            << "as a decimal fraction: ";
         cin >> trate;
         p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
      }
      while (cin.get() != '\n')
      {
      }
   }

   cout << endl;

   for (int i = 0; i < Clients; i++)
   {
      p_clients[i]->viewAccount();
      cout << endl;
   }

   for (int i = 0; i < Clients; i++)
   {
      delete p_clients[i]; // free memory
   }

   cout << "Done.\n";

   return 0;
}
