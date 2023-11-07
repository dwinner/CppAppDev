/**
 * WEB Get
 * Usage: web_get http://example.com
 */

#include <stdio.h>
#include "network.h"
#include "web_get.h"

int main(int argc, char *argv[])
{
#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return EXIT_FAILURE;
   }
#endif

   if (argc < 2)
   {
      fprintf(stderr, "usage: web_get url\n");
      return EXIT_FAILURE;
   }

   char *url = argv[1];
   char *hostname, *port, *path;
   parse_url(url, &hostname, &port, &path);
   SOCKET server = connect_to_host(hostname, port);
   send_request(server, hostname, port, path);

   const clock_t start_time = clock();

#define RESPONSE_SIZE 32768

   char response[RESPONSE_SIZE + 1];
   char *p = response, *q;
   char *end = response + RESPONSE_SIZE;
   char *body = 0;

   enum
   {
      length,
      chunked,
      connection
   };

   int encoding = 0;
   int remaining = 0;

   while (1)
   {
      if (((double) (clock() - start_time) / CLOCKS_PER_SEC) > TIMEOUT)
      {
         fprintf(stderr, "timeout after %.2f seconds\n", TIMEOUT);
         return EXIT_FAILURE;
      }

      if (p == end)
      {
         fprintf(stderr, "out of buffer space\n");
         return EXIT_FAILURE;
      }

      fd_set reads;
      FD_ZERO(&reads);
      FD_SET(server, &reads);

      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 200000;

      if (select(server + 1, &reads, 0, 0, &timeout) < 0)
      {
         fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
         return EXIT_FAILURE;
      }

      if (FD_ISSET(server, &reads))
      {
         int bytes_received = recv(server, p, end - p, 0);
         if (bytes_received < 1)
         {
            if (encoding == connection && body)
            {
               printf("%.*s", (int) (end - body), body);
            }

            printf("\nConnection closed by peer.\n");
            break;
         }

#ifdef NDEBUG
         printf("Received (%d bytes): '%.*s'", bytes_received, bytes_received, p);
#endif

         p += bytes_received;
         *p = 0;

         if (!body && (body = strstr(response, "\r\n\r\n")))
         {
            *body = 0;
            body += 4;

#ifdef NDEBUG
            printf("Received Headers:\n%s\n", response);
#endif

            q = strstr(response, "\nContent-Length: ");
            if (q)
            {
               encoding = length;
               q = strchr(q, ' ');
               q += 1;
               remaining = strtol(q, 0, 10);
            }
            else
            {
               q = strstr(response, "\nTransfer-Encoding: chunked");
               if (q)
               {
                  encoding = chunked;
                  remaining = 0;
               }
               else
               {
                  encoding = connection;
               }
            }

            printf("\nReceived Body:\n");
         }

         if (body)
         {
            if (encoding == length)
            {
               if (p - body >= remaining)
               {
                  printf("%.*s", remaining, body);
                  break;
               }
            }
            else if (encoding == chunked)
            {
               do
               {
                  if (remaining == 0)
                  {
                     if ((q = strstr(body, "\r\n")))
                     {
                        remaining = strtol(body, 0, 16);
                        if (!remaining)
                        {
                           goto finish;
                        }

                        body = q + 2;
                     }
                     else
                     {
                        break;
                     }
                  }
                  if (remaining && p - body >= remaining)
                  {
                     printf("%.*s", remaining, body);
                     body += remaining + 2;
                     remaining = 0;
                  }
               } while (!remaining);
            }
         }
      }
   }

   finish:

   printf("\nClosing socket...\n");
   CLOSESOCKET(server);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}
