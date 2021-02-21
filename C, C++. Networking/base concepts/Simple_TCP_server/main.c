/**
 * Stream socket server demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * The port users will be connecting to
 */
#define PORT "3490"

/**
 * How many pending connections queue will hold
 */
#define BACKLOG 10

void sig_child_handler(int s);

/**
 * @brief Get sockaddr, IPv4 or IPv6:
 * @param sa socket struct pointer entity
 * @return IPv4 or IPv6 socket internet address
 */
void *get_in_addr(struct sockaddr *sa);

int main()
{
   printf("hello from Simple_TCP_server!\n");
   return 0;
}

void sig_child_handler(int s)
{
   (void)s; // quiet unused variable warning

   // waitpid() might overwrite errno, so we save restore it:
   int savedErrno = errno;

   while (waitpid(-1, NULL, WNOHANG) > 0)
   {      
   }

   errno = savedErrno;
}

void *get_in_addr(struct sockaddr *sa)
{
   if (sa->sa_family == AF_INET)
   {
      struct in_addr* sin_addr = &((struct sockaddr_in*)sa)->sin_addr;
      return sin_addr;
   }
   else
   {
      return &((struct sockaddr_in6*)sa)->sin6_addr;
   }
}
