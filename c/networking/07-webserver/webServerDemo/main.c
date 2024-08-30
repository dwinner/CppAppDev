#include <stdio.h>
#include <stdbool.h>
#include "web_srv_api.h"

/**
 * @brief Default host
 */
static char *const default_host = "localhost";

/**
 * @brief Default port
 */
static char *const default_port = "8080";

int main()
{
#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
#ifndef NDEBUG
      fprintf(stderr, "Failed to initialize.\n");
#endif

      return EXIT_FAILURE;
   }
#endif

   const SOCKET server = create_socket(default_host, default_port);

   while (true)
   {
      fd_set reads = wait_on_clients(server);
      if (FD_ISSET(server, &reads))
      {
         ClientInfoT *client = get_client(-1);
         client->socket = accept(server,
                                 (struct sockaddr *) &(client->address),
                                 &(client->address_length));
         if (!ISVALIDSOCKET(client->socket))
         {
#ifndef NDEBUG
            fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
#endif

            return EXIT_FAILURE;
         }

#ifndef NDEBUG
         printf("New connection from %s.\n", get_client_address(client));
#endif
      }

      ClientInfoT *client = clients;
      while (client)
      {
         ClientInfoT *next = client->next;
         if (FD_ISSET(client->socket, &reads))
         {
            if (MAX_REQUEST_SIZE == client->received)
            {
               send_400(client);
               client = next;
               continue;
            }

            const int recvCnt = recv(client->socket,
                                     client->request + client->received,
                                     MAX_REQUEST_SIZE - client->received, 0);
            if (recvCnt < 1)
            {
#ifndef NDEBUG
               printf("Unexpected disconnect from %s.\n", get_client_address(client));
#endif

               drop_client(client);
            }
            else
            {
               client->received += recvCnt;
               client->request[client->received] = 0;
               char *query = strstr(client->request, "\r\n\r\n");
               if (query)
               {
                  *query = 0;
                  if (strncmp("GET /", client->request, 5))
                  {
                     send_400(client);
                  }
                  else
                  {
                     const char *path = client->request + 4;
                     char *endPath = strstr(path, " ");
                     if (!endPath)
                     {
                        send_400(client);
                     }
                     else
                     {
                        *endPath = 0;
                        serve_resource(client, path);
                     }
                  }
               }
            }
         }

         client = next;
      }
   }

#ifndef NDEBUG
   printf("\nClosing socket...\n");
#endif

   CLOSESOCKET(server);

#if defined(_WIN32)
   WSACleanup();
#endif

#ifndef NDEBUG
   printf("Finished.\n");
#endif

   return EXIT_SUCCESS;
}
