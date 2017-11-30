// Fig. 6.18: fig06_18.c
// Linear search of an array.
#include <stdio.h>
#define SIZE 100

// function prototype
size_t linearSearch(const int array[], int key, size_t size); 

// function main begins program execution
int main(void)
{   
   int a[SIZE]; // create array a

   // create some data
   for (size_t x = 0; x < SIZE; ++x) { 
      a[x] = 2 * x;
   } 

   printf("Enter integer search key: ");
   int searchKey; // value to locate in array a
   scanf("%d", &searchKey);

   // attempt to locate searchKey in array a 
   size_t index = linearSearch(a, searchKey, SIZE);

   // display results
   if (index != -1) {
      printf("Found value at index %d\n", index);
   } 
   else {
      puts("Value not found");
   } 
}

// compare key to every element of array until the location is found 
// or until the end of array is reached; return index of element 
// if key is found or -1 if key is not found                               
size_t linearSearch(const int array[], int key, size_t size)      
{                                                                    
   // loop through array                                          
   for (size_t n = 0; n < size; ++n) {                                    
                                                                     
      if (array[n] == key) {                                     
         return n; // return location of key                      
      }                                                  
   }                                                    
                                                                     
   return -1; // key not found                                    
}
