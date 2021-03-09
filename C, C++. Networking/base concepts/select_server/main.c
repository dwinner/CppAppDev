/**
 * Cheezy multiperson char server
 */

#if defined(_WIN32)
#error This program doesn't support Windows
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
   printf("Hello, World!\n");
   return 0;
}