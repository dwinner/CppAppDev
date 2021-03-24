// qsort_ex.c : qsort() example
// -------------------------------------------------------------
// void qsort( void *array, size_t n, size_t size, int (*compare)( const void *, const void *) );

#include <stdlib.h>
#include <stdio.h>

int strptrcmp(const void *sp1, const void *sp2);

int main()
{
   char *words[] =
       {
           "Then", "he", "shouted", "What", "I",
           "didn't", "hear", "what", "you", "said"
       };

   int n = sizeof(words) / sizeof(char *);

   qsort(words, n, sizeof(char *), strptrcmp);

   for (int j = 0; j < n; j++)
   {
      puts(words[j]);
   }
}

#include <string.h>

// Compare two strings by reference.
int strptrcmp(const void *sp1, const void *sp2)
{
   // qsort() passes a pointer to the pointer:
   // dereference it to pass a char * to strcmp.
   const char *s1 = *(char **) sp1;
   const char *s2 = *(char **) sp2;

   return strcmp(s1, s2);
}
