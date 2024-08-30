/**
 * Simple web client supporting TLS
 * Usage: ./https_get https://example.org
 */

#include <stdbool.h>
#include "ssl_network.h"
#include "ssl_web_get.h"

#define RESPONSE_SIZE 32768

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

   SSL_library_init();
   OpenSSL_add_all_algorithms();
   SSL_load_error_strings();

   SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
   if (ctx == NULL)
   {
      fprintf(stderr, "SSL_CTX_new() failed.\n");
      return EXIT_FAILURE;
   }

   if (argc < 2)
   {
      fprintf(stderr, "usage: web_get url\n");
      return EXIT_FAILURE;
   }

   char *url = argv[1];

   char *hostname, *port, *path;
   parse_url(url, &hostname, &port, &path);

   SOCKET server = connect_to_host(hostname, port);

   SSL *ssl = SSL_new(ctx);
   if (ssl == NULL)
   {
      fprintf(stderr, "SSL_new() failed.\n");
      return EXIT_FAILURE;
   }

   if (!SSL_set_tlsext_host_name(ssl, hostname))
   {
      fprintf(stderr, "SSL_set_tlsext_host_name() failed.\n");
      ERR_print_errors_fp(stderr);
      return EXIT_FAILURE;
   }

   SSL_set_fd(ssl, server);
   if (SSL_connect(ssl) == -1)
   {
      fprintf(stderr, "SSL_connect() failed.\n");
      ERR_print_errors_fp(stderr);
      return EXIT_FAILURE;
   }

   printf("SSL/TLS using %s\n", SSL_get_cipher(ssl));

   X509 *cert = SSL_get_peer_certificate(ssl);
   if (cert == NULL)
   {
      fprintf(stderr, "SSL_get_peer_certificate() failed.\n");
      return EXIT_FAILURE;
   }

   char *tmp;
   if ((tmp = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0)))
   {
      printf("subject: %s\n", tmp);
      OPENSSL_free(tmp);
   }

   if ((tmp = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0)))
   {
      printf("issuer: %s\n", tmp);
      OPENSSL_free(tmp);
   }

   X509_free(cert);

   send_request(ssl, hostname, port, path);

   const clock_t startTime = clock();
   char response[RESPONSE_SIZE + 1];
   char *pResp = response, *query;
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

   while (true)
   {
      if ((((double) (clock() - startTime)) / CLOCKS_PER_SEC) > TIMEOUT)
      {
         fprintf(stderr, "timeout after %.2f seconds\n", TIMEOUT);
         return EXIT_FAILURE;
      }

      if (pResp == end)
      {
         fprintf(stderr, "out of buffer space\n");
         return EXIT_FAILURE;
      }

      fd_set reads;
      FD_ZERO(&reads);
      FD_SET(server, &reads);

      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 200;

      if (select(server + 1, &reads, 0, 0, &timeout) < 0)
      {
         fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
         return EXIT_FAILURE;
      }

      if (FD_ISSET(server, &reads))
      {
         int bytesReceived = SSL_read(ssl, pResp, (int) (end - pResp));
         if (bytesReceived < 1)
         {
            if (encoding == connection && body)
            {
               printf("%.*s", (int) (end - body), body);
            }

            printf("\nConnection closed by peer.\n");
            break;
         }

         printf("Received (%d bytes): '%.*s'", bytesReceived, bytesReceived, pResp);

         pResp += bytesReceived;
         *pResp = 0;

         if (!body && (body = strstr(response, "\r\n\r\n")))
         {
            *body = 0;
            body += 4;

            printf("Received Headers:\n%s\n", response);

            query = strstr(response, "\nContent-Length: ");
            if (query)
            {
               encoding = length;
               query = strchr(query, ' ');
               query += 1;
               remaining = (int) strtol(query, 0, 10);
            }
            else
            {
               query = strstr(response, "\nTransfer-Encoding: chunked");
               if (query)
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
               if (pResp - body >= remaining)
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
                     if ((query = strstr(body, "\r\n")))
                     {
                        remaining = (int) strtol(body, 0, 16);
                        if (!remaining)
                        {
                           goto finish;
                        }

                        body = query + 2;
                     }
                     else
                     {
                        break;
                     }
                  }

                  if (pResp - body >= remaining)
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
   SSL_shutdown(ssl);
   CLOSESOCKET(server);
   SSL_free(ssl);
   SSL_CTX_free(ctx);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}
