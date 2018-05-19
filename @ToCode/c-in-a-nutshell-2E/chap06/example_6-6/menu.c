// Example 6-6. A switch statement
// menu.c : A switch statement to process the user’s selection from a menu.

#include <stdio.h>
#include <stdlib.h>

// Handle a command that the user selects from a menu.
// ---------------------------------------------------
// Declare other functions used:
int menu( void );             // Prints the menu and returns
                              // a character that the user types.
void action1( void ),
     action2( void );

int main()
{
   _Bool done = 0;
printf("\talert \a\a\a\n");
   while( !done)
     switch ( menu() )         // Jump depending on the result of menu().
     {
      case 'a':
      case 'A': action1();        // Carry out action 1.
                break;            // Don't do any other "actions."
      case 'b':
      case 'B': action2();        // Carry out action 2.
                break;            // Don't do the default "action."
      case 'q':
      case 'Q': done = 1;
                break;
      default:  putchar('\a');    // If no recognized command,
     }                            // output an alert.

   return EXIT_SUCCESS;
}

void action1( void )  {  puts("action1 . . ."); }

void action2( void )  {  puts("action2 . . ."); }

#include <ctype.h>
int menu( void )               // Prints the menu and returns
{                              // a character that the user types.
   static char menuStr[] =
   "\n               A = Action 1"
   "\n               B = Action 2"
   "\n               Q = Quit the program"
   "\n Your choice:  ";

   fputs( menuStr,stdout);

   int choice = 0;
   do 
     if( (choice = getchar()) == EOF)
         choice = 'Q'; 
   while( isspace(choice) );

   return choice;
}
