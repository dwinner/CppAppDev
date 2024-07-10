#if defined(_WIN32)
#error This program does not support Windows.
#endif

#include "../network.h"
#include <ctype.h>
#include <stdlib.h>

int main()
{
   printf("Configuring local address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bind_address;
   getaddrinfo(0, "8080", &hints, &bind_address);


   printf("Creating socket...\n");
   SOCKET socket_listen;
   socket_listen = socket(bind_address->ai_family,
                          bind_address->ai_socktype, bind_address->ai_protocol);
   if (!ISVALIDSOCKET(socket_listen))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   printf("Binding socket to local address...\n");
   if (bind(socket_listen,
            bind_address->ai_addr, bind_address->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   freeaddrinfo(bind_address);

   printf("Listening...\n");
   if (listen(socket_listen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   printf("Waiting for connections...\n");

   while (1)
   {
      struct sockaddr_storage client_address;
      socklen_t client_len = sizeof(client_address);
      SOCKET socket_client = accept(socket_listen,
                                    (struct sockaddr *) &client_address, &client_len);
      if (!ISVALIDSOCKET(socket_client))
      {
         fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
         return 1;
      }

      char address_buffer[100];
      getnameinfo((struct sockaddr *) &client_address,
                  client_len, address_buffer, sizeof(address_buffer), 0, 0,
                  NI_NUMERICHOST);
      printf("New connection from %s\n", address_buffer);

      int pid = fork();

      if (pid == 0)
      { //child process
         CLOSESOCKET(socket_listen);
         while (1)
         {
            char read[1024];
            int bytes_received = recv(socket_client, read, 1024, 0);
            if (bytes_received < 1)
            {
               CLOSESOCKET(socket_client);
               exit(0);
            }

            int j;
            for (j = 0; j < bytes_received; ++j)
               read[j] = toupper(read[j]);
            send(socket_client, read, bytes_received, 0);
         }
      }

      CLOSESOCKET(socket_client);

   } //while(1)

   printf("Closing listening socket...\n");
   CLOSESOCKET(socket_listen);

#if defined(_WIN32)
   WSACleanup();
#endif


   printf("Finished.\n");

   return 0;
}
