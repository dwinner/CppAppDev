// Fig. 8.31: fig08_31.c
// Using function memchr
#include <stdio.h>
#include <string.h>

int main(void)
{ 
   const char *s = "This is a string"; // initialize char pointer

   printf("%s\'%c\'%s\"%s\"\n", 
      "The remainder of s after character ", 'r', 
      " is found is ", (char *) memchr(s, 'r', 16));
} 

/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
