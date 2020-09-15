listing 1
/* The Bubble Sort. */
void bubble(char *items, int count)
{
  register int a, b;
  register char t;

  for(a=1; a < count; ++a)
    for(b=count-1; b >= a; --b) {
      if(items[b-1] > items[b]) {
        /* exchange elements */
        t = items[b-1];
        items[b-1] = items[b];
        items[b] = t;
      }
    }
}

listing 2
/* Sort Driver */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void bubble(char *items, int count);

int main(void)
{
  char s[255];

  printf("Enter a string:");
  gets(s);
  bubble(s, strlen(s));
  printf("The sorted string is: %s.\n", s);

  return 0;
}

listing 3
/* The Shaker Sort. */
void shaker(char *items, int count)
{
  register int a;
  int exchange;
  char t;

  do {
    exchange = 0;
    for(a=count-1; a > 0; --a) {
      if(items[a-1] > items[a]) {
        t = items[a-1];
        items[a-1] = items[a];
        items[a] = t;
        exchange = 1;
      }
    }

    for(a=1; a < count; ++a) {
      if(items[a-1] > items[a]) {
        t = items[a-1];
        items[a-1] = items[a];
        items[a] = t;
        exchange = 1;
      }
    }
  } while(exchange); /* sort until no exchanges take place */
}

listing 4
/* The Selection Sort. */
void select(char *items, int count)
{
  register int a, b, c;
  int exchange;
  char t;

  for(a=0; a < count-1; ++a) {
    exchange = 0;
    c = a;
    t = items[a];
    for(b=a+1; b < count; ++b) {
      if(items[b] < t) {
        c = b;
        t = items[b];
        exchange = 1;
      }
    }
    if(exchange) {
      items[c] = items[a];
      items[a] = t;
    }
  }
}

listing 5
/* The Insertion Sort. */
void insert(char *items, int count)
{

  register int a, b;
  char t;

  for(a=1; a < count; ++a) {
    t = items[a];
    for(b=a-1; (b >= 0) && (t < items[b]); b--)
      items[b+1] = items[b];
    items[b+1] = t;
  }
}

listing 6
/* The Shell Sort. */
void shell(char *items, int count)
{

  register int i, j, gap, k;
  char x, a[5];

  a[0]=9; a[1]=5; a[2]=3; a[3]=2; a[4]=1;

  for(k=0; k < 5; k++) {
    gap = a[k];
    for(i=gap; i < count; ++i) {
      x = items[i];
      for(j=i-gap; (x < items[j]) && (j >= 0); j=j-gap)
        items[j+gap] = items[j];
      items[j+gap] = x;
    }
  }
}

listing 7
/* Quicksort setup function. */
void quick(char *items, int count)
{
  qs(items, 0, count-1);
}

/* The Quicksort. */
void qs(char *items, int left, int right)
{
  register int i, j;
  char x, y;

  i = left; j = right;
  x = items[(left+right)/2];

  do {
    while((items[i] < x) && (i < right)) i++;
    while((x < items[j]) && (j > left)) j--;

    if(i <= j) {
      y = items[i];
      items[i] = items[j];
      items[j] = y;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs(items, left, j);
  if(i < right) qs(items, i, right);
}

listing 8
/* A Quicksort for strings. */
void quick_string(char items[][10], int count)
{
  qs_string(items, 0, count-1);
}

void qs_string(char items[][10], int left, int right)
{
  register int i, j;
  char *x;
  char temp[10];

  i = left; j = right;
  x = items[(left+right)/2];

  do {
    while((strcmp(items[i],x) < 0) && (i < right)) i++;
    while((strcmp(items[j],x) > 0) && (j > left)) j--;
    if(i <= j) {
      strcpy(temp, items[i]);
      strcpy(items[i], items[j]);
      strcpy(items[j], temp);
      i++; j--;
   }
  } while(i <= j);

  if(left < j) qs_string(items, left, j);
  if(i < right) qs_string(items, i, right);
}

listing 9
#include <stdio.h>
#include <string.h>

void quick_string(char items[][10], int count);
void qs_string(char items[][10], int left, int right);

char str[][10] = { "one",
                   "two",
                   "three",
                   "four"
                 };

int main(void)
{
  int i;

  quick_string(str, 4);

  for(i=0; i<4; i++) printf("%s ", str[i]);

  return 0;
}

listing 10
struct address {
  char name[40];
  char street[40];
  char city[20];
  char state[3];
  char zip[11];
};

listing 11
/* A Quicksort for structures of type address. */
void quick_struct(struct address items[], int count)
{
  qs_struct(items,0,count-1);
}

void qs_struct(struct address items[], int left, int right)
{

  register int i, j;
  char *x;
  struct address temp;

  i = left; j = right;
  x = items[(left+right)/2].zip;

  do {
    while((strcmp(items[i].zip,x) < 0) && (i < right)) i++;
    while((strcmp(items[j].zip,x) > 0) && (j > left)) j--;
    if(i <= j) {
      temp = items[i];
      items[i] = items[j];
      items[j] = temp;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs_struct(items, left, j);
  if(i < right) qs_struct(items, i, right);
}

listing 12
/* Disk sort for structures of type address. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ELEMENTS 4  /* This is an arbitrary number
                           that should be determined
                           dynamically for each list. */

struct address {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  char zip[11];
} ainfo;

struct address addrs[NUM_ELEMENTS] = {
  "A. Alexander", "101 1st St", "Olney", "Ga", "55555",
  "B. Bertrand", "22 2nd Ave", "Oakland", "Pa", "34232",
  "C. Carlisle", "33 3rd Blvd", "Ava", "Or", "92000",
  "D. Dodger", "4 Fourth Dr", "Fresno", "Mi", "45678"
};

void quick_disk(FILE *fp, int count);
void qs_disk(FILE *fp, int left, int right);
void swap_all_fields(FILE *fp, long i, long j);
char *get_zip(FILE *fp, long rec);

int main(void)
{
  FILE *fp;

  /* first, create a file to sort */
  if((fp=fopen("mlist", "wb"))==NULL) {
    printf("Cannot open file for write.\n");
    exit(1);
  }
  printf("Writing unsorted data to disk.\n");
  fwrite(addrs, sizeof(addrs), 1, fp);
  fclose(fp);

  /* now, sort the file */
  if((fp=fopen("mlist", "rb+"))==NULL) {
    printf("Cannot open file for read/write.\n");
    exit(1);
  }

  printf("Sorting disk file.\n");
  quick_disk(fp, NUM_ELEMENTS);
  fclose(fp);
  printf("List sorted.\n");

  return 0;
}

/* A Quicksort for files. */
void quick_disk(FILE *fp, int count)
{
  qs_disk(fp, 0, count-1);
}

void qs_disk(FILE *fp, int left, int right)
{
  long int i, j;
  char x[100];

  i = left; j = right;

  strcpy(x, get_zip(fp, (long)(i+j)/2)); /* get the middle zip */

  do {
    while((strcmp(get_zip(fp,i),x) < 0) && (i < right)) i++;
    while((strcmp(get_zip(fp,j),x) > 0) && (j > left)) j--;

    if(i <= j) {
      swap_all_fields(fp, i, j);
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs_disk(fp, left, (int) j);
  if(i < right) qs_disk(fp, (int) i, right);
}

void swap_all_fields(FILE *fp, long i, long j)
{
  char a[sizeof(ainfo)], b[sizeof(ainfo)];

  /* first read in record i and j */
  fseek(fp, sizeof(ainfo)*i, SEEK_SET);
  fread(a, sizeof(ainfo), 1, fp);

  fseek(fp, sizeof(ainfo)*j, SEEK_SET);
  fread(b, sizeof(ainfo), 1, fp);

  /* then write them back in opposite slots */
  fseek(fp, sizeof(ainfo)*j, SEEK_SET);
  fwrite(a, sizeof(ainfo), 1, fp);
  fseek(fp, sizeof(ainfo)*i, SEEK_SET);
  fwrite(b, sizeof(ainfo), 1, fp);
}

/* Return a pointer to the zip code */
char *get_zip(FILE *fp, long rec)
{
  struct address *p;

  p = &ainfo;

  fseek(fp, rec*sizeof(ainfo), SEEK_SET);
  fread(p, sizeof(ainfo), 1, fp);

  return ainfo.zip;
}

listing 13
int sequential_search(char *items, int count, char key)
{
  register int t;

  for(t=0; t < count; ++t)
    if(key == items[t]) return t;
  return -1; /* no match */
}

listing 14
/* The Binary search. */
int binary_search(char *items, int count, char key)
{
  int low, high, mid;

  low = 0; high = count-1;
  while(low <= high) {
    mid = (low+high)/2;
    if(key < items[mid]) high = mid-1;
    else if(key > items[mid]) low = mid+1;
    else return mid; /* found */
  }
  return -1;
}

