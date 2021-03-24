// strxfrm_ex.c : strxfrm() example
// -------------------------------------------------------------
// size_t strxfrm( char * restrict dest,
//                 const char * restrict src,
//                 size_t n );

#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_COUNT    1024
#define PAIR_COUNT   8

typedef struct string_pair
{
   char *original;
   char *x_formed;
} String_Pair_t;

String_Pair_t string_pairs[PAIR_COUNT] =
    {
        {"Chávez",        NULL},
        {"Carron",        NULL},
        {"Canoso",        NULL},
        {"Cañoso",        NULL},
        {"Carteño",       NULL},
        {"Cortillo",      NULL},
        {"Cortiluz S.A.", NULL},
        {"Corriando",     NULL}
    };

/**
 * Space to catch each strxfrm() result.
 */
char xform_buffer[MAX_COUNT];

/**
 * Defined externally.
 * @param p1 1st str
 * @param p2 2nd str
 * @return cmp result
 */
int string_pair_cmp(const void *p1, const void *p2);

int main()
{
   // Use the host system's locale setting.
   setlocale(LC_COLLATE, "");

#ifdef _DEBUG
   printf("The locale is %s.\n", setlocale(LC_COLLATE, NULL));
#endif

   for (int i = 0; i < PAIR_COUNT; i++)
   {
      string_pairs[i].x_formed = malloc(strxfrm(xform_buffer, string_pairs[i].original, MAX_COUNT) + 1);
      if (string_pairs[i].x_formed != NULL)
      {
         strcpy(string_pairs[i].x_formed, xform_buffer);
      }
   }

   qsort(string_pairs, PAIR_COUNT, sizeof(String_Pair_t), string_pair_cmp);

   for (int i = 0; i < PAIR_COUNT; i++)
   {
      puts(string_pairs[i].original);
   }

   return 0;
}

int string_pair_cmp(const void *sp1, const void *sp2)
{
   const char *s1 = ((String_Pair_t *) sp1)->x_formed;
   const char *s2 = ((String_Pair_t *) sp2)->x_formed;

   return strcmp(s1, s2);
}
