/**
 * Testing stack of pointers
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Stack.h"

const int Num = 10;

int main()
{
   std::srand(std::time(0));
   std::cout << "Please enter stack size: ";
   int stacksize;
   std::cin >> stacksize;

   // create an empty stack with stacksize slots
   Stack<const char *> stack(stacksize);

   // in basket
   const char *in[Num] =
      {
         " 1: Hank Gilgamesh", " 2: Kiki Ishtar",
         " 3: Betty Rocker", " 4: Ian Flagranti",
         " 5: Wolfgang Kibble", " 6: Portia Koop",
         " 7: Joy Almondo", " 8: Xaverie Paprika",
         " 9: Juan Moore", "10: Misha Mache"
      };
   // out basket
   const char *out[Num];

   int processed = 0;
   int nextin = 0;
   while (processed < Num)
   {
      if (stack.isEmpty())
      {
         stack.push(in[nextin++]);
      }
      else if (stack.isFull())
      {
         stack.pop(out[processed++]);
      }
      else if (std::rand() % 2 && nextin < Num)
      {
         stack.push(in[nextin++]);
      }
      else
      {
         stack.pop(out[processed++]);
      }
   }

   for (int i = 0; i < Num; i++)
   {
      std::cout << out[i] << std::endl;
   }

   std::cout << "Bye\n";

   return 0;
}
