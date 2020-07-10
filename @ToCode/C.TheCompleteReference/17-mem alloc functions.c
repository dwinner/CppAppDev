listing 1
#include <stdlib.h>
#include <stdio.h>

float *get_mem(void)
{
  float *p;

  p = calloc(100, sizeof(float));
  if(!p) {
    printf("Allocation Error\n");
    exit(1);
  }
  return p;
}

listing 2
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  char *str[100];
  int i;

  for(i=0; i<100; i++) {
    if((str[i] = malloc(128))==NULL) {
      printf("Allocation Error\n");
      exit(1);
    }
    gets(str[i]);
  }

  /* now free the memory */
  for(i=0; i<100; i++) free(str[i]);

  return 0;
}

listing 3
struct addr {
  char name[40];
  char street[40];
  char city[40];
  char state[3];
  char zip[10];
};

struct addr *get_struct(void)
{
  struct addr *p;

  if((p = malloc(sizeof(struct addr)))==NULL) {
    printf("Allocation Error\n");
    exit(1);
  }
  return p;
}

listing 4
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  char *p;

  p = malloc(17);
  if(!p) {
    printf("Allocation Error\n");
    exit(1);
  }

  strcpy(p, "This is 16 chars");

  p = realloc(p, 18);
  if(!p) {
    printf("Allocation Error\n");
    exit(1);
  }

  strcat(p, ".");

  printf(p);

  free(p);

  return 0;
}

