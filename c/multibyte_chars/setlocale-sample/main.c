// setlocale_ex.c : setlocale() example
// -------------------------------------------------------------
// char *setlocale( int category,
//                  const char *locale_name );

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 80

int main()
{
   char name[MAX_STRING];
   char locale[MAX_STRING];
   char *newlocale;
   int i;

   printf("Who are you? ");
   fgets(name, sizeof(name), stdin);

   printf("What is your locale? ");
   fgets(locale, sizeof(locale), stdin);

   name[strlen(name) - 1] = '\0';     // Chomp off the newlines.
   locale[strlen(locale) - 1] = '\0';

   newlocale = setlocale(LC_CTYPE, locale);
   if (newlocale == NULL)
   {
      printf("Sorry, couldn't change the locale to %s.\n"
             "The current locale is %s. ",
             locale, setlocale(LC_CTYPE, NULL));
   }
   else
   {
      printf("The new locale is %s. ", newlocale);
   }

   name[0] = toupper(name[0]);   // Force the first letter to uppercase.

   i = 1;
   if (isupper(name[i]))       // Is the second letter also uppercase?
   {
      while (name[i] != '\0')    // If so, force all the rest to lowercase.
      {
         name[i] = tolower(name[i]);
         ++i;
      }
   }

   printf("Hello there, %s!\n", name);

   return 0;
}
