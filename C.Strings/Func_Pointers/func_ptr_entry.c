/**
 * Uses function pointers
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ARRAY_CAPACITY 81

char showMenu(void);
void eatLine(void); // read through end of line
void show(void (*fp)(char*), char* str);
void toUpper(char*); // convert string to upper case
void toLower(char*); // convert string to lower case
void transpose(char*); // transpose cases
void dummy(char*); // leave string unaltered

int main(void)
{
   char line[ARRAY_CAPACITY];
   char copy[ARRAY_CAPACITY];
   char choice;
   void (*pfun)(char*); // points a function having a char* argument and no return value;

   puts("Enter a string (empty line to quit):");
   while (gets_s(line, ARRAY_CAPACITY) != NULL && line[0] != '\0')
   {
      while ((choice = showMenu()) != '\n')
      {
         switch (choice)
         {
         case 'u':
            pfun = toUpper;
            break;
         case 'l':
            pfun = toLower;
            break;
         case 't':
            pfun = transpose;
            break;
         case 'o':
            pfun = dummy;
            break;
         default:
            pfun = dummy;
            break;
         }

         strcpy_s(copy, ARRAY_CAPACITY, line); // make copy for show()
         show(pfun, copy); // use selected function
      }

      puts("Enter a string (empty line to quit):");
   }

   puts("Buy!");

   return 0;
}

char showMenu(void)
{
   char ans;
   puts("Enter menu choice:");
   puts("u) uppercase      l) lowercase");
   puts("t) transposed case o) original case");
   puts("n) next string");
   ans = getchar(); // get response
   ans = tolower(ans); // convert to lowercase
   eatLine(); // dispose of rest of line
   while (strchr("ulton", ans) == NULL)
   {
      puts("Please enter a u, l, t, o, or n:");
      ans = tolower(getchar());
      eatLine();
   }

   return ans;
}

void eatLine(void)
{
   while (getchar() != '\n')
   {
   }
}

void toUpper(char* str)
{
   while (*str)
   {
      *str = toupper(*str);
      str++;
   }
}

void toLower(char* str)
{
   while (*str)
   {
      *str = tolower(*str);
      str++;
   }
}

void transpose(char* str)
{
   while (*str)
   {
      if (islower(*str))
      {
         *str = toupper(*str);
      }
      else if (isupper(*str))
      {
         *str = tolower(*str);
      }

      str++;
   }
}

void dummy(char* str)
{
   // leaves string unchanged
}

void show(void (*fp)(char*), char* str)
{
   (*fp)(str); // apply chosen function to str
   puts(str);
}
