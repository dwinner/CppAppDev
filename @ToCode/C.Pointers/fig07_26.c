// Fig. 7.26: fig07_26.c
// Multipurpose sorting program using function pointers.
#include <stdio.h>
#define SIZE 10

// prototypes
void bubble(int work[], size_t size, int (*compare)(int a, int b));
int ascending(int a, int b);
int descending(int a, int b);

int main(void)
{
   // initialize unordered array a
   int a[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};

   printf("%s", "Enter 1 to sort in ascending order,\n" 
          "Enter 2 to sort in descending order: ");
   int order; // 1 for ascending order or 2 for descending order
   scanf("%d", &order);

   puts("\nData items in original order");
   
   // output original array
   for (size_t counter = 0; counter < SIZE; ++counter) {
      printf("%5d", a[counter]);
   } 

   // sort array in ascending order; pass function ascending as an
   // argument to specify ascending sorting order
   if (order == 1) {
      bubble(a, SIZE, ascending);
      puts("\nData items in ascending order");
   }  
   else { // pass function descending
      bubble(a, SIZE, descending);
      puts("\nData items in descending order");
   }

   // output sorted array
   for (size_t counter = 0; counter < SIZE; ++counter) {
      printf("%5d", a[counter]);   
   } 

   puts("\n");
} 

// multipurpose bubble sort; parameter compare is a pointer to
// the comparison function that determines sorting order
void bubble(int work[], size_t size, int (*compare)(int a, int b))
{
   void swap(int *element1Ptr, int *element2ptr); // prototype

   // loop to control passes
   for (unsigned int pass = 1; pass < size; ++pass) {

      // loop to control number of comparisons per pass
      for (size_t count = 0; count < size - 1; ++count) {

         // if adjacent elements are out of order, swap them
         if ((*compare)(work[count], work[count + 1])) {
            swap(&work[count], &work[count + 1]);
         } 
      } 
   } 
}

// swap values at memory locations to which element1Ptr and 
// element2Ptr point
void swap(int *element1Ptr, int *element2Ptr)
{
   int hold = *element1Ptr;
   *element1Ptr = *element2Ptr;
   *element2Ptr = hold;
}

// determine whether elements are out of order for an ascending
// order sort                                               
int ascending(int a, int b)                                  
{                                                              
   return b < a; // should swap if b is less than a         
}

// determine whether elements are out of order for a descending
// order sort                                               
int descending(int a, int b)                                 
{                                                              
   return b > a; // should swap if b is greater than a      
}
