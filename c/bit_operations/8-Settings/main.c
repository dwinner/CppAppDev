/**
 * Settings via bit masks
 */

#if !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "main.h"

int main()
{
   Font sample = 1 | (12 << SIZE_SHIFT) | LEFT | ITALIC;

   while (doMenu(&sample) != 'q')
   {
   }

   puts("Bye!");
   return EXIT_SUCCESS;
}

char doMenu(Font* pFont)
{
   char response;

   showFont(*pFont);
   showMenu();
   response = getChoice("fsabiuq");
   switch (response)
   {
   case 'f':
      getId(pFont);
      break;
   case 's':
      getSize(pFont);
      break;
   case 'a':
      getAlign(pFont);
      break;
   case 'b':
      *pFont ^= BOLD;
      break;
   case 'i':
      *pFont ^= ITALIC;
      break;
   case 'u':
      *pFont ^= UNDERLINE;
      break;
   case 'q':
      break;
   default:
      fprintf(stderr, "menu problem");
   }

   return response;
}

char getChoice(const char* pChoice)
{
   char ch;

   ch = getchar();
   ch = tolower(ch);
   eatLine();
   while (strchr(pChoice, ch) == NULL)
   {
      printf("Please enter one of the following: %s\n", pChoice);
      ch = tolower(getchar());
      eatLine();
   }

   return ch;
}

void showFont(Font font)
{
   printf("\n%4s %4s %9s %3s %3s %3s\n",
          "ID", "SIZE", "ALIGNMENT", "B", "I", "U");
   printf("%4lu %4lu", font & ID_MASK, (font & SIZE_MASK) >> SIZE_SHIFT);
   switch (font & ALIGN_MASK)
   {
   case LEFT:
      printf("%7s", "left");
      break;
   case RIGHT:
      printf("%7s", "right");
      break;
   case CENTER:
      printf("%7s", "center");
      break;
   default:
      printf("%7s", "unknown");
      break;
   }

   printf("%8s %3s %3s\n\n",
          (font & BOLD) == BOLD ? "on" : "off",
          (font & ITALIC) == ITALIC ? "on" : "off",
          (font & UNDERLINE) == UNDERLINE ? "on" : "off");
}

void getId(Font* pFont)
{
   int id;

   printf("Enter font ID (0-255): ");
   scanf("%d", &id);
   id &= ID_MASK;
   *pFont |= id;
   eatLine();
}

void getSize(Font* pFont)
{
   int size;

   printf("Enter font size (0-127): ");
   scanf("%d", &size);
   *pFont |= (size << SIZE_SHIFT) & SIZE_MASK;
   eatLine();
}

void getAlign(Font* pFont)
{
   puts("Select alignment:");
   puts("l)left   c)center   r)right");
   switch (getChoice("lcr"))
   {
   case 'l':
      *pFont &= ~ALIGN_MASK;
      *pFont |= LEFT;
      break;
   case 'c':
      *pFont &= ~ALIGN_MASK;
      *pFont |= CENTER;
      break;
   case 'r':
      *pFont &= ~ALIGN_MASK;
      *pFont |= RIGHT;
      break;
   default:
      fprintf(stderr, "alignment problem");
   }
}
