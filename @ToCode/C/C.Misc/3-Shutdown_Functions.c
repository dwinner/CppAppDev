// Fig. 14.4: fig14_04.c
// Using the exit and atexit functions
#include <stdio.h>
#include <stdlib.h>

void print(void); // prototype

int main(void)
{ 
   atexit(print); // register function print
   puts("Enter 1 to terminate program with function exit"
      "\nEnter 2 to terminate program normally");
   int answer; // user's menu choice
   scanf("%d", &answer);

   // call exit if answer is 1
   if (answer == 1) { 
      puts("\nTerminating program with function exit");
      exit(EXIT_SUCCESS);
   } 

   puts("\nTerminating program by reaching the end of main");
} 

// display message before termination              
void print(void)                                    
{                                                      
   puts("Executing function print at program "       
      "termination\nProgram terminated");     
}
