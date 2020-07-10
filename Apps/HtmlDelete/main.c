/**
 * Удаляем HTML-разметку
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IN  0
#define OUT 1

int main()
{
   int c = 0;
   int state = OUT;
   int tagState = OUT;
   char tagbuff[2048];
   char *ptrl = NULL;

   ptrl = tagbuff;
   while ((c = getchar()) != EOF)
   {
      /* копируем тег в tagbuff */
      if (c == '<' || c == '&')
      {
         state = IN;
      }

      if (state == IN)
      {
         *ptrl++ = (char) c;
      }

      if (c == '>' || c == ';')
      {
         state = OUT;
         *ptrl++ = '\0';

         /* Ищем тэги, css-стили, javascript */
         if (strstr(tagbuff, "<s") != 0 || strstr(tagbuff, "<S") != 0)
         {
            tagState = IN;
         }

         if (strstr(tagbuff, "</") != 0)
         {
            tagState = OUT;
         }

         /* ? */
         if (strstr(tagbuff, "nbsp") != 0 || strstr(tagbuff, "NBSP") != 0)
         {
            printf(" ");
         }

         ptrl = tagbuff;
      }

      /* Не в тэгэ, выводим символ */
      if (state == OUT && tagState == OUT && c != '>' && c != ';')
      {
         printf("%c", c);
      }
   }

   return EXIT_SUCCESS;
}