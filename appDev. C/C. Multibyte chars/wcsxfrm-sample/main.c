// wcsxfrm_ex.c : wcsxfrm() example
// -------------------------------------------------------------
// size_t wcsxfrm( wchar_t * restrict dest,
//                 const wchar_t * restrict src,
//                 size_t n );

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct stringpair
{
   wchar_t *original;
   wchar_t *xformed;
} Stringpair_t;

int stringpaircmp(const void *p1, const void *p2);

int main()
{
   wchar_t *originals[] =
       {
           L"Chávez",
           L"Carron",
           L"Canoso",
           L"Cañoso",
           L"Carteño",
           L"Corriando",
           L"Carilo",
           L"Carillón",
       };
   wchar_t xformbuffer[1024];

   /* Make an array of structures out of the strings and their
      xformations */

   const int elementcount = sizeof(originals) / sizeof(wchar_t *);
   Stringpair_t stringpairs[elementcount];

   setlocale(LC_ALL, "es_US.UTF-8");   // Set the locale to US Spanish
   wprintf(L"Sorting order in the locale %s:\n", setlocale(LC_COLLATE, NULL));

   for (int i = 0; i < elementcount; i++)
   {
      stringpairs[i].original = originals[i];
      stringpairs[i].xformed = malloc(wcsxfrm(xformbuffer, originals[i], 1024));
      if (stringpairs[i].xformed != NULL)
      {
         wcscpy(stringpairs[i].xformed, xformbuffer);
      }
   }

   qsort(stringpairs, elementcount, sizeof(Stringpair_t), stringpaircmp);

   for (int i = 0; i < elementcount; i++)
   {
      fputws(stringpairs[i].original, stdout);
      fputwc(L'\n', stdout);
   }
} // end of main()

/* A comparison function for use by qsort. Uses wcscmp() rather
 * that wcscoll(), assuming strings are paired with their wcsxfrm()
 * results in a Stringpair_t structure.
*/
int stringpaircmp(const void *p1, const void *p2)
{
   const Stringpair_t *sp1 = (Stringpair_t *) p1;
   const Stringpair_t *sp2 = (Stringpair_t *) p2;

   return wcscmp(sp1->xformed, sp2->xformed);
}
