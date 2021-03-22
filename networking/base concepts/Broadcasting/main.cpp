/**
 * datagram "client" like talker.c, except this one can broadcast
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/**
 * @brief the port users will be connecting to
 */
constexpr int serverport = 4950;

int main(int argc, char* argv[])
{
   int sock_fd;
   struct sockaddr_in their_addr{}; // connector's address information
   struct hostent* host_env;
   int num_bytes;
   int broadcast = 1;

   if (argc != 3)
   {
      fprintf(stderr, "usage: broadcaster hostname message\n");
      exit(1);
   }

   if ((host_env = gethostbyname(argv[1])) == nullptr)
   {
      // get the host info
      perror("gethostbyname");
      exit(1);
   }

   if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("socket");
      exit(1);
   }

   // this call is what allows broadcast packets to be sent:
   if (setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                  sizeof broadcast) == -1)
   {
      perror("setsockopt (SO_BROADCAST)");
      exit(1);
   }

   their_addr.sin_family = AF_INET; // host byte order
   their_addr.sin_port = htons(serverport); // short, network byte order
   their_addr.sin_addr = *reinterpret_cast<in_addr*>(host_env->h_addr);
   memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

   if ((num_bytes = sendto(sock_fd, argv[2], strlen(argv[2]), 0,
                           reinterpret_cast<sockaddr*>(&their_addr), sizeof their_addr)) == -1)
   {
      perror("sendto");
      exit(1);
   }

   printf("sent %d bytes to %s\n",
          num_bytes,
          inet_ntoa(their_addr.sin_addr));

   close(sock_fd);

   return 0;
}
