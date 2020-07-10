listing 1
/* Copy one file to another. */
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

  if((in=fopen(argv[1], "rb")) == NULL) {
    printf("Cannot open input file.\n");
    exit(1);
  }
  if((out=fopen(argv[2], "wb")) == NULL) {
    printf("Cannot open output file.\n");
    exit(1);
  }

  while(!feof(in)) {
    ch = getc(in);
    if(ferror(in)) {
      printf("Read Error");
      clearerr(in);
      break;
    } else {
      if(!feof(in)) putc(ch, out);
      if(ferror(out)) {
        printf("Write Error");
        clearerr(out);
        break;
      }
    }
  }
  fclose(in);
  fclose(out);

  return 0;
}

listing 2
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;

  if((fp=fopen("test", "rb"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  if(fclose(fp)) printf("File close error.\n");

  return 0;
}

listing 3
/*
   Assume that fp has been opened for read operations.
*/
while(!feof(fp)) getc(fp);

listing 4
/*
  Assume that fp points to a stream opened for write
  operations.
*/

while(!done) {
  putc(info, fp);
  if(ferror(fp)) {
    printf("File Error\n");
    exit(1);
  }
}

listing 5
/*
  Assume that fp is associated with an output file.
*/

for(i=0; i<MAX; i++) {
  fwrite(buf, sizeof(some_type), 1, fp);
  fflush(fp);
}

listing 6
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char ch;

  if((fp=fopen(argv[1],"r"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  while((ch=fgetc(fp)) != EOF) {
    printf("%c", ch);
  }
  fclose(fp);

  return 0;
}

listing 7
FILE *fp;
fpos_t file_loc;
.
.
.
fgetpos(fp, &file_loc);

listing 8
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char str[128];

  if((fp=fopen(argv[1], "r"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  while(!feof(fp)) {
    if(fgets(str, 126, fp)) printf("%s", str);
  }

  fclose(fp);

  return 0;
}

listing 9
FILE *fp;

if ((fp = fopen("test", "w"))==NULL) {
  printf("Cannot open file.\n");
  exit(1);
}

listing 10
FILE *fp;

if((fp=fopen("test", "rb+"))==NULL) {
  printf("Cannot open file.\n");
  exit(1);
}

listing 11
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;

  if((fp=fopen("test", "wb"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  fprintf(fp, "this is a test %d %f", 10, 20.01);
  fclose(fp);

  return 0;
}

listing 12
void write_string(char *str, FILE *fp)
{
  while(*str) if(!ferror(fp)) fputc(*str++, fp);
}

listing 13
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  float bal[5] = { 1.1F, 2.2F, 3.3F, 4.4F, 5.5F };
  int i;

  /* write the values */
  if((fp=fopen("test", "wb"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  if(fwrite(bal, sizeof(float), 5, fp) != 5) 
    printf("File read error.");
  fclose(fp);

  /* read the values */
  if((fp=fopen("test", "rb"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  if(fread(bal, sizeof(float), 5, fp) != 5) {
    if(feof(fp)) printf("Premature end of file.");
    else printf("File read error.");
  }
  fclose(fp);

  for(i=0; i<5; i++)
    printf("%f ", bal[i]);  

  return 0;
}

listing 14
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;

  printf("This will display on the screen.\n");

  if((fp=freopen("OUT", "w" ,stdout))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  printf("This will be written to the file OUT.");

  fclose(fp);

  return 0;
}

listing 15
char str[80];
float f;

fscanf(fp, "%s%f", str, &f);

listing 16
struct addr {
  char name[40];
  char street[40];
  char city[40];
  char state[3];
  char zip[10];
} info;

void find(long int client_num)
{
  FILE *fp;

  if((fp=fopen("mail", "rb")) == NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  /* find the proper structure */
  fseek(fp, client_num*sizeof(struct addr), SEEK_SET);

  /* read the data into memory */
  fread(&info, sizeof(struct addr), 1, fp);

  fclose(fp);
}

listing 17
long int i;

if((i=ftell(fp)) == -1L)
  printf("A file error has occurred.\n");

listing 18
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  float f=12.23;

  if((fp=fopen("test", "wb"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  fwrite(&f, sizeof(float), 1, fp);

  fclose(fp);

  return 0;
}

listing 19
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char ch;

  if((fp=fopen(argv[1], "r"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  while((ch=getc(fp))!=EOF) {
    printf("%c", ch);
  }

  fclose(fp);

  return 0;
}

listing 20
#include <stdio.h>

int main(void)
{
  char s[256], *p;

  p = s;

  while((*p++ = getchar())!= '\n') ;
  *p = '\0'; /* add null terminator */
  printf(s);

  return 0;
}

listing 21
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  char fname[128];

  printf("Enter filename: ");
  gets(fname);

  if((fp=fopen(fname, "r"))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  fclose(fp);

  return 0;
}

listing 22
printf("Hi %c %d %s", 'c', 10, "there!");

listing 23
int i;

printf("This is a test%n", &i);
printf("%d", i);

listing 24
#include <stdio.h>

int main(void)
{
  /* This prints "this is a test" left justified
     in 20 character field.
  */
  printf("%-20s", "this is a test");

  /* This prints a float with 3 decimal places in a 10
     character field. The output will be "     12.235".
  */
  printf("%10.3f", 12.234657);

  return 0;
}

listing 25
#include <stdio.h>
#include <string.h>

int main(void)
{
  char str[80];

  strcpy(str, "this is an example");

  puts(str);

  return 0;
}

listing 26
#include <stdio.h>

int main(int argc, char *argv[])
{
  if(remove(argv[1])) printf("Remove Error");

  return 0;
}

listing 27
#include <stdio.h>

int main(int argc, char *argv[])
{
  if(rename(argv[1], argv[2]) != 0) printf("Rename Error");

  return 0;
}

listing 28
void re_read(FILE *fp)
{
  /* read once */
  while(!feof(fp)) putchar(getc(fp));

  rewind(fp);

  /* read twice */
  while(!feof(fp)) putchar(getc(fp));
}

listing 29
scanf("%d%d", &r, &c);

listing 30
scanf("%d%*c%d", &x, &y);

listing 31
scanf("%20s", address);

listing 32
scanf("%c%c%c", &a, &b, &c);

listing 33
scanf("%dt%d", &x, &y);

listing 34
%[ABC]

listing 35
%[A-Z]

listing 36
#include <stdio.h>

int main(void)
{
  char str[80], str2[80];
  int i;

  /* read a string and an integer */
  scanf("%s%d", str, &i);

  /* read up to 79 chars into str */
  scanf("%79s", str);

  /* skip the integer between the two strings */
  scanf("%s%*d%s", str, str2);

  return 0;
}

listing 37
#include <stdio.h>

int main(void)
{
  char str[80];
  int i;

  sscanf("hello 1 2 3 4 5", "%s%d", str, &i);
  printf("%s %d", str, i);

  return 0;
}

listing 38
FILE *temp;

if((temp=tmpfile())==NULL) {
  printf("Cannot open temporary work file.\n");
  exit(1);
}

listing 39
#include <stdio.h>

int main(void)
{
  char name[40];
  int i;

  for(i=0; i<3; i++) {
    tmpnam(name);
    printf("%s ", name);
  }

  return 0;
}

listing 40
void read_word(FILE *fp, char *token)
{
  while(isalpha(*token=getc(fp))) token++;
  ungetc(*token, fp);
}

listing 41
#include <stdio.h>
#include <stdarg.h>

void print_message(char *format, ...);

int main(void)
{
  print_message("Cannot open file %s.", "test");

  return 0;
}

void print_message(char *format, ...)
{
  va_list ptr; /* get an arg ptr */

  /* initialize ptr to point to the first argument after the
     format string
  */
  va_start(ptr, format);

  /* print out message */
  vprintf(format, ptr);

  va_end(ptr);
}

