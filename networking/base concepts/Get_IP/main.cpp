/*
** getip.c -- a hostname lookup demo
*/

#include <cstdio>
#include <cstdlib>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      // error check the command line
      fprintf(stderr, "usage: getip address\n");
      exit(1);
   }

   char* host_name = argv[1];
   struct hostent* host_env = gethostbyname(host_name);
   if (host_env == nullptr)
   {
      // get the host info
      herror("gethostbyname");
      exit(1);
   }

   printf("Host name  : %s\n", host_env->h_name);
   printf("IP Address : %s\n", inet_ntoa(*reinterpret_cast<in_addr*>(host_env->h_addr)));

   return 0;
}
