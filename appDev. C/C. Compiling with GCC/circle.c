// circle.c: Calculate the areas of circles and
// print them in ncurses mode
// $ gcc -o circle  circle.c -lncurses

#include <curses.h>               // Console control functions

double circularArea(double r);  // Function for the math
void circle();                    // Function for output

int main()        // Starts and stops curses display mode
{

/* Set up the console behavior: */
   (void) initscr();      // Initialize the curses system
   keypad(stdscr, TRUE);  // Enable keyboard mapping
   (void) nonl();         // Disable line-end translation
   (void) cbreak();       // Take single input characters

/* Run the circle routine: */
   circle();
   printw("Press any key to exit.");
   refresh();             // Put the output on the screen

/* Finish: */
   getch();               // Wait for user to press a key
   endwin();              // Shut down curses console
   return 0;
}

// The circle.c program from Example 1.1, but replacing the
// standard library function printf() with printw() from the
// ncurses library.
void circle()
{
   double radius = 1.0, area = 0.0;
   printw("    Areas of Circles\n\n");
   printw("     Radius          Area\n"
          "-------------------------\n");
   area = circularArea(radius);
   printw("%10.1f     %10.2f\n", radius, area);
   radius = 5.0;
   area = circularArea(radius);
   printw("%10.1f     %10.2f\n", radius, area);
}

// Return the area of a circle with radius r
double circularArea(double r)
{
   const double pi = 3.1415926536; // Pi is a constant
   return pi * r * r;
}
