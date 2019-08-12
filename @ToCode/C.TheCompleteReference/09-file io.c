listing 1
FILE *fp;
fp = fopen("test", "w");

listing 2
FILE *fp;

if ((fp = fopen("test","w"))==NULL) {
  printf("Cannot open file.\n");
  exit(1);
}

listing 3
do {
  ch = getc(fp);
} while(ch!=EOF);

listing 4
/* KTOD: A key to disk program. */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char ch;

  if(argc!=2) {
    printf("You forgot to enter the filename.\n");
    exit(1);
  }

  if((fp=fopen(argv[1], "w"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  do {
    ch = getchar();
    putc(ch, fp);
  } while (ch != '$');

  fclose(fp);

  return 0;
}

listing 5
/* DTOS: A program that reads files and displays them
         on the screen. */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char ch;

  if(argc!=2) {
    printf("You forgot to enter the filename.\n");
    exit(1);
  }

  if((fp=fopen(argv[1], "r"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  ch = getc(fp);   /* read one character */

  while (ch!=EOF) {
    putchar(ch);  /* print on screen */
    ch = getc(fp);
  }

  fclose(fp);

  return 0;
}

listing 6
while(!feof(fp)) ch = getc(fp);

listing 7
/* Copy a file. */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *in, *out;
  char ch;

  if(argc!=3) {
    printf("You forgot to enter a filename.\n");
    exit(1);
  }

  if((in=fopen(argv[1], "rb"))==NULL) {
    printf("Cannot open source file.\n");
    exit(1);
  }
  if((out=fopen(argv[2], "wb")) == NULL) {
    printf("Cannot open destination file.\n");
    exit(1);
  }

  /* This code actually copies the file. */
  while(!feof(in)) {
    ch = getc(in);
    if(!feof(in)) putc(ch, out);
  }

  fclose(in);
  fclose(out);

  return 0;
}

listing 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char str[80];
  FILE *fp;

  if((fp = fopen("TEST", "w"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  do {
    printf("Enter a string (CR to quit):\n");
    gets(str);
    strcat(str, "\n");  /* add a newline */
    fputs(str, fp);
  } while(*str!='\n');

  return 0;
}

listing 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char str[80];
  FILE *fp;

  if((fp = fopen("TEST", "w+"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  do {
    printf("Enter a string (CR to quit):\n");
    gets(str);
    strcat(str, "\n");  /* add a newline */
    fputs(str, fp);
  } while(*str!='\n');

  /* now, read and display the file */
  rewind(fp);  /* reset file position indicator to
                  start of the file. */
  while(!feof(fp)) {
    fgets(str, 79, fp);
    printf(str);
  }

  return 0;
}

listing 10
/* The program substitutes spaces for tabs
   in a text file and supplies error checking. */

#include <stdio.h>
#include <stdlib.h>

#define TAB_SIZE 8
#define IN 0
#define OUT 1

void err(int e);

int main(int argc, char *argv[])
{
  FILE *in, *out;
  int tab, i;
  char ch;

  if(argc!=3) {
    printf("usage: detab <in> <out>\n");
    exit(1);
  }

  if((in = fopen(argv[1], "rb"))==NULL) {
    printf("Cannot open %s.\n", argv[1]);
    exit(1);
  }

  if((out = fopen(argv[2], "wb"))==NULL) {
    printf("Cannot open %s.\n", argv[1]);
    exit(1);
  }

  tab = 0;
  do {
    ch = getc(in);
    if(ferror(in)) err(IN);

    /* if tab found, output appropriate number of spaces */
    if(ch=='\t') {
      for(i=tab; i<8; i++) {
        putc(' ', out);
        if(ferror(out)) err(OUT);
      }
      tab = 0;
    }
    else {
      putc(ch, out);
      if(ferror(out)) err(OUT);
      tab++;
      if(tab==TAB_SIZE) tab = 0;
      if(ch=='\n' || ch=='\r') tab = 0;
    }
  } while(!feof(in));
  fclose(in);
  fclose(out);

  return 0;
}

void err(int e)
{
  if(e==IN) printf("Error on input.\n");
  else printf("Error on output.\n");
  exit(1);
}

listing 11
/* Double check before erasing. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  char str[80];

  if(argc!=2) {
    printf("usage: xerase <filename>\n");
    exit(1);
  }

  printf("Erase %s? (Y/N): ", argv[1]);
  gets(str);

  if(toupper(*str)=='Y')
    if(remove(argv[1])) {
      printf("Cannot erase file.\n");
      exit(1);
    }
  return 0; 
}

listing 12
/* Write some non-character data to a disk file
   and read it back.  */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  double d = 12.23;
  int i = 101;
  long l = 123023L;

  if((fp=fopen("test", "wb+"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  fwrite(&d, sizeof(double), 1, fp);
  fwrite(&i, sizeof(int), 1, fp);
  fwrite(&l, sizeof(long), 1, fp);

  rewind(fp);

  fread(&d, sizeof(double), 1, fp);
  fread(&i, sizeof(int), 1, fp);
  fread(&l, sizeof(long), 1, fp);

  printf("%f %d %ld", d, i, l);

  fclose(fp);

  return 0;
}

listing 13
struct struct_type {
  float balance;
  char name[80];
} cust;

listing 14
fwrite(&cust, sizeof(struct struct_type), 1, fp);

listing 15
/* A simple mailing list example using an array of structures. */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct addr {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
} addr_list[MAX];

void init_list(void), enter(void);
void delete(void), list(void);
void load(void), save(void);
int menu_select(void), find_free(void);

int main(void)
{
  char choice;

  init_list(); /* initialize the structure array */
  for(;;) {
    choice = menu_select();
    switch(choice) {
      case 1: enter();
        break;
      case 2: delete();
        break;
      case 3: list();
        break;
      case 4: save();
        break;
      case 5: load();
        break;
      case 6: exit(0);
    }
  }

  return 0;
}

/* Initialize the list. */
void init_list(void)
{
  register int t;

  for(t=0; t<MAX; ++t) addr_list[t].name[0] = '\0';
}

/* Get a menu selection. */
int menu_select(void)
{
  char s[80];
  int c;

  printf("1. Enter a name\n");
  printf("2. Delete a name\n");
  printf("3. List the file\n");
  printf("4. Save the file\n");
  printf("5. Load the file\n");
  printf("6. Quit\n");
  do {
    printf("\nEnter your choice: ");
    gets(s);
    c = atoi(s);
  } while(c<0 || c>6);
  return c;
}

/* Input addresses into the list. */
void enter(void)
{
  int slot;
  char s[80];

  slot = find_free();

  if(slot==-1) {
    printf("\nList Full");
    return;
  }

  printf("Enter name: ");
  gets(addr_list[slot].name);

  printf("Enter street: ");
  gets(addr_list[slot].street);

  printf("Enter city: ");
  gets(addr_list[slot].city);

  printf("Enter state: ");
  gets(addr_list[slot].state);

  printf("Enter zip: ");
  gets(s);
  addr_list[slot].zip = strtoul(s, '\0', 10);
}

/* Find an unused structure. */
int find_free(void)
{
  register int t;

  for(t=0; addr_list[t].name[0] && t<MAX; ++t) ;

  if(t==MAX) return -1; /* no slots free */
  return t;
}

/* Delete an address. */
void delete(void)
{
  register int slot;
  char s[80];

  printf("enter record #: ");
  gets(s);
  slot = atoi(s);

  if(slot>=0 && slot < MAX)
    addr_list[slot].name[0] = '\0';
}

/* Display the list on the screen. */
void list(void)
{
  register int t;

  for(t=0; t<MAX; ++t) {
    if(addr_list[t].name[0]) {
      printf("%s\n", addr_list[t].name);
      printf("%s\n", addr_list[t].street);
      printf("%s\n", addr_list[t].city);
      printf("%s\n", addr_list[t].state);
      printf("%lu\n\n", addr_list[t].zip);
    }
  }
  printf("\n\n");
}

/* Save the list. */
void save(void)
{
  FILE  *fp;
  register int i;

  if((fp=fopen("maillist", "wb"))==NULL) {
    printf("Cannot open file.\n");
    return;
  }

  for(i=0; i<MAX; i++)
    if(*addr_list[i].name)
      if(fwrite(&addr_list[i],
         sizeof(struct addr), 1, fp)!=1)
           printf("File write error.\n");

  fclose(fp);
}

/* Load the file. */
void load(void)
{
  FILE  *fp;
  register int i;

  if((fp=fopen("maillist", "rb"))==NULL) {
    printf("Cannot open file.\n");
    return;
  }

  init_list();
  for(i=0; i<MAX; i++)
    if(fread(&addr_list[i],
       sizeof(struct addr), 1, fp)!=1) {
         if(feof(fp)) break;
         printf("File read error.\n");
    }

  fclose(fp);
}

listing 16
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;

  if(argc!=3) {
    printf("Usage: SEEK filename byte\n");
    exit(1);
  }

  if((fp = fopen(argv[1], "rb"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  if(fseek(fp, atol(argv[2]), SEEK_SET)) {
    printf("Seek error.\n");
    exit(1);
  }

  printf("Byte at %ld is %c.\n", atol(argv[2]), getc(fp));
  fclose(fp);

  return 0;
}

listing 17
fseek(fp, 9*sizeof(struct addr), SEEK_SET);

listing 18
/* fscanf() - fprintf() example */
#include <stdio.h>
#include <io.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  char s[80];
  int t;

  if((fp=fopen("test", "w")) == NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  printf("Enter a string and a number: ");
  fscanf(stdin, "%s%d", s, &t); /* read from keyboard */

  fprintf(fp, "%s %d", s, t); /* write to file */
  fclose(fp); 

  if((fp=fopen("test","r")) == NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  fscanf(fp, "%s%d", s, &t); /* read from file */
  fprintf(stdout, "%s %d", s, t); /* print on screen */

  return 0;
}

listing 19
int putchar(char c)
{
  return putc(c, stdout);
}

listing 20
char str[255];
fgets(str, 80, stdin);

listing 21
#include <stdio.h>
#include <string.h>

int main(void)
{
  char str[80];
  int i;

  printf("Enter a string: ");
  fgets(str, 10, stdin);

  /* remove newline, if present */
  i = strlen(str)-1;
  if(str[i]=='\n') str[i] = '\0';

  printf("This is your string: %s", str);

  return 0;
}

listing 22
#include <stdio.h>

int main(void)
{
  char str[80];

  printf("Enter a string: ");
  gets(str);
  printf(str);

  return 0;
}

listing 23
#include <stdio.h>

int main(void)
{
  char str[80];

  freopen("OUTPUT", "w", stdout);

  printf("Enter a string: ");
  gets(str);
  printf(str);

  return 0;
}

