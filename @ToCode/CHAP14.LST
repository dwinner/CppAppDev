listing 1
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getc(stdin);
    if(ch == '.') break;
    if(isalnum(ch)) printf("%c is alphanumeric\n", ch);
  }

  return 0;
}

listing 2
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
  ch = getchar();
  if(ch == '.') break;
  if(isalpha(ch)) printf("%c is a letter\n", ch);
  }

  return 0;
}

listing 3
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
  ch = getchar();
  if(ch == '.') break;
  if(isblank(ch)) printf("%c is a word separator\n", ch);
  }

  return 0;
}

listing 4
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
   ch = getchar( );
   if(ch == '.') break;
   if(iscntrl(ch)) printf("%c is a control char\n", ch);
  }

  return 0;
}

listing 5
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(ch == '.') break;
    if(isdigit(ch)) printf("%c is a digit\n", ch);
  }

  return 0;
}

listing 6
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(isgraph(ch)) printf("%c is printable\n", ch);
    if(ch == '.') break;
  }

  return 0;
}

listing 7
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(ch == '.') break;
    if(islower(ch)) printf("%c is lowercase\n", ch);
  }

  return 0;
}

listing 8
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(isprint(ch)) printf("%c is printable\n",ch);
    if(ch == '.') break;
  }

  return 0;
}

listing 9
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(ispunct(ch)) printf("%c is punctuation\n", ch);
    if(ch == '.') break;
  }

  return 0;
}

listing 10
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
  ch = getchar();
  if(isspace(ch)) printf("%c is white space\n", ch);
  if(ch == '.') break;
  }

  return 0;
}

listing 11
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(ch == '.') break;
    if(isupper(ch)) printf("%c is uppercase\n", ch);
  }

  return 0;
}

listing 12
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char ch;

  for(;;) {
    ch = getchar();
    if(ch == '.') break;
    if(isxdigit(ch)) printf("%c is hexadecimal digit\n", ch);
  }

  return 0;
}

listing 13
#include <stdio.h>
#include <string.h>

int main(void)
{
  char *p;

  p = memchr("this is a test", ' ', 14);
  printf(p);

  return 0;
}

listing 14
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int outcome, len, l1, l2;

  if(argc!=3) {
    printf("Incorrect number of arguments.");
    exit(1);
  }

  /* find the length of shortest string */
  l1 = strlen(argv[1]);
  l2 = strlen(argv[2]);
  len = l1 < l2 ? l1:l2;

  outcome = memcmp(argv[1], argv[2], len);
  if(!outcome) printf("Equal");
  else if(outcome<0) printf("First less than second.");
  else printf("First greater than second.");

  return 0;
}

listing 15
#include <stdio.h>
#include <string.h>

#define SIZE 80

int main(void)
{
  char buf1[SIZE], buf2[SIZE];

  strcpy(buf1, "When, in the course of...");
  memcpy(buf2, buf1, SIZE);
  printf(buf2);

  return 0;
}

listing 16
#include <stdio.h>
#include <string.h>

#define SIZE 80

int main(void)
{
  char str[SIZE], *p;

  strcpy(str, "When, in the course of...");
  p = str + 10;

  memmove(str, p, SIZE);
  printf("result after shift: %s", str);

  return 0;
}

listing 17
memset(buf, '\0', 100);
memset(buf, 'X', 10);
printf(buf);

listing 18
#include <stdio.h>
#include <string.h>

int main(void)
{
  char s1[80], s2[80];

  gets(s1);
  gets(s2);

  strcat(s2, s1);
  printf(s2);

  return 0;
}

listing 19
#include <stdio.h>
#include <string.h>

int main(void)
{
  char *p;

  p = strchr("this is a test", ' ');
  printf(p);

  return 0;
}

listing 20
int password(void)
{
  char s[80];

  printf("Enter password: ");
  gets(s);

  if(strcmp(s, "pass")) {
    printf("Invalid Password\n");
    return 0;
  }
  return 1;
}

listing 21
if(strcoll("hi", "hi")) printf("Equal");

listing 22
char str[80];
strcpy(str, "hello");

listing 23
#include <string.h>
#include <stdio.h>

int main(void)
{
  int len;

  len = strcspn("this is a test", "ab");
  printf("%d", len);

  return 0;
}

listing 24
printf(strerror(10));

listing 25
printf("%d", strlen("hello"));

listing 26
#include <stdio.h>
#include <string.h>

int main(void)
{
  char s1[80], s2[80];
  unsigned int len;

  gets(s1);
  gets(s2);

  /* compute how many chars will actually fit */
  len = 79-strlen(s2);

  strncat(s2, s1, len);
  printf(s2);

  return 0;
}

listing 27
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if(argc!=3) {
    printf("Incorrect number of arguments.");
    exit(1);
  }

  if(!strncmp(argv[1], argv[2], 8))
    printf("The strings are the same.\n");

  return 0;
}

listing 28
char str1[128], str2[80];

gets(str1);
strncpy(str2, str1, 79);

listing 29
#include <stdio.h>
#include <string.h>

int main(void)
{
  char *p;

  p = strpbrk("this is a test", " absj");
  printf(p);

  return 0;
}

listing 30
#include <string.h>
#include <stdio.h>

int main(void)
{
  char *p;

  p = strrchr("this is a test", 'i');
  printf(p);

  return 0;
}

listing 31
#include <string.h>
#include <stdio.h>

int main(void)
{
  int len;

  len = strspn("this is a test", "siht ");
  printf("%d", len);

  return 0;
}

listing 32
#include <string.h>
#include <stdio.h>

int main(void)
{
  char *p;

  p = strstr("this is a test", "is");
  printf(p);

  return 0;
}

listing 33
#include <stdio.h>
#include <string.h>

int main(void)
{
  char *p;

  p = strtok("The summer soldier, the sunshine patriot", " ");
  printf(p);
  do {
    p = strtok('\0', ", ");
    if(p) printf("|%s", p);
  } while(p);

  return 0;
}

listing 34
strxfrm(s1, s2, 10);

listing 35
putchar(tolower('Q'));

listing 36
putchar(toupper('a'));

