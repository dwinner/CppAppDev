// perror_ex.c : perror() example
// -------------------------------------------------------------
// void perror( const char *string );

#include <stdio.h>
#include <errno.h>

#define MSGLEN_MAX 256

int main(int argc, char *argv[])
{
   FILE *fp;
   char msgbuf[MSGLEN_MAX] = "";

   if ((fp = fopen("nonexistentfile", "r")) == NULL)
   {
      snprintf(msgbuf, MSGLEN_MAX, "%s, function %s, file %s, line %d",
               argv[0], __func__, __FILE__, __LINE__);
      perror(msgbuf);
      return errno;
   }

   return 0;
}
