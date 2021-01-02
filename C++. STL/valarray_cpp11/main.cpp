#include <iostream>
#include <valarray>
#include <algorithm>
#include <cstdlib>

const int arSize = 10;

int main()
{
   using namespace std;

   valarray<double> numbers(arSize);
   int i;
   for (i = 0; i < arSize; i++)
   {
      numbers[i] = rand() + i * 1.23;
   }

   for (i = 0; i < arSize; i++)
   {
      cout << numbers[i] << ' ';
   }

   cout << endl;
   sort(begin(numbers), end(numbers));
   for (i = 0; i < arSize; i++)
   {
      cout << numbers[i] << ' ';
   }

   cout << endl;

   return 0;
}
