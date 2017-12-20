/**
 * Binary search of a sorted array
 */
#include <stdio.h>
#define SIZE 15

size_t binarySearch(const int b[], int searchKey, size_t low, size_t high);
void printHeader(void);
void printRow(const int b[], size_t low, size_t mid, size_t high);

int main(void)
{
   int a[SIZE]; // create array a

   // create data
   for (size_t i = 0; i < SIZE; ++i)
   {
      a[i] = 2 * i;
   }

   printf("%s", "Enter a number between 0 and 28: ");
   int key; // value to locate in array a
   scanf_s("%d", &key);

   printHeader();

   // Search for key in array a
   const size_t result = binarySearch(a, key, 0, SIZE - 1);

   // display results
   if (result != (size_t)-1)
   {
      printf("\n%d found at index %d\n", key, result);
   }
   else
   {
      printf("\n%d not found\n", key);
   }

   return 0;
}

/**
 * \brief Print one row of output showing the current partof the array being processed
 * \param b Array
 * \param low low element
 * \param mid middle element
 * \param high high element
 */
void printRow(const int b[], const size_t low, const size_t mid, const size_t high)
{
   // loop through entire array
   for (size_t i = 0; i < SIZE; ++i)
   {
      if (i < low || i > high) // display spaces if outside current subarray range
      {
         printf("%s", "    ");
      }
      else if (i == mid) // display middle element
      {
         printf("%3d*", b[i]);
      }
      else // display other elements in subarray
      {
         printf("%3d", b[i]);
      }
   }

   puts(""); // start a new line of output
}

/**
 * \brief Print a header for the output
 */
void printHeader(void)
{
   puts("\nSubscripts:");

   // output column header
   for (unsigned int i = 0; i < SIZE; ++i)
   {
      printf("%3u", i);
   }

   puts(""); // start new line of output

   // output line of - characters
   for (unsigned int i = 1; i <= 4 * SIZE; ++i)
   {
      printf("%s", "-");
   }

   puts(""); // start new line of output
}

/**
 * \brief Binary search of a sorted array
 * \param b Array
 * \param searchKey Search key
 * \param low low index
 * \param high high index
 * \return found index or -1 if the search element hasn't been found
 */
size_t binarySearch(const int b[], const int searchKey, size_t low, size_t high)
{
   // loop until low index is greater than high index
   while (low <= high)
   {
      // determine middle element of subarray being searched
      const size_t middle = (low + high) / 2;

      // display subarray used in this loop iteration
      printRow(b, low, middle, high);

      // if searchKey matched middle element, return middle
      if (searchKey == b[middle])
      {
         return middle;
      }

      if (searchKey < b[middle]) // if searchKey is less than middle element, set new high
      {
         high = middle - 1; // search low end of array
      }
      else // if searchKey is greater than middle element, set low
      {
         low = middle + 1; // search high end of array
      }
   }

   return -1; // searchKey not found
}
