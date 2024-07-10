/**
 * Using a queue that has a nested class
 */

#include <iostream>
#include <string>
#include "QueueTP.h"

int main()
{
   using std::string;
   using std::cin;
   using std::cout;

   QueueTP<string> queue(5);
   string temp;

   while (!queue.isFull())
   {
      cout << "Please enter your name. You will be "
              "served in the order of arrival.\n"
              "name: ";
      getline(cin, temp);
      queue.enqueue(temp);
   }

   cout << "The queue is full. Processing begins!\n";

   while (!queue.isEmpty())
   {
      queue.dequeue(temp);
      cout << "Now processing " << temp << "...\n";
   }

   return 0;
}
