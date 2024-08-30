/**
 * Using an enumeration
 */
#include <stdio.h>

// enumeration constants represent months of the year            
enum months
{
   Jan = 1,
   Feb,
   Mar,
   Apr,
   May,
   Jun,
   Jul,
   Aug,
   Sep,
   Oct,
   Nov,
   Dec
};

int main(void)
{
   // initialize array of pointers
   const char* monthName[] =
   {
      "",
      "January",
      "February",
      "March",
      "April",
      "May",
      "June",
      "July",
      "August",
      "September",
      "October",
      "November",
      "December"
   };

   for (enum months month = Jan; month <= Dec; month++)
   {
      printf("%2d%11s\n", month, monthName[month]);
   }

   return 0;
}
