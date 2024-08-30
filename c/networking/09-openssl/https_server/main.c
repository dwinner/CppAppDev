/**
 * Http server implementation with TLS supporting
 */

#include "ssl_network.h"
#include "ssl_web_srv.h"

int main()
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

   SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());
   if (ctx == NULL)
   {
      fprintf(stderr, "SSL_CTX_new() failed.\n");
      return EXIT_FAILURE;
   }

   if (!SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM)
       || !SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM))
   {
      fprintf(stderr, "SSL_CTX_use_certificate_file() failed.\n");
      ERR_print_errors_fp(stderr);
      return EXIT_FAILURE;
   }

   SOCKET server = create_socket(0, "8080");
   while (1)
   {
      fd_set reads = wait_on_clients(server);
      if (FD_ISSET(server, &reads))
      {
         client_info_t *client = get_client(-1);
         client->socket = accept(server,
                                 (struct sockaddr *) &(client->address),
                                 &(client->address_length));

         if (!ISVALIDSOCKET(client->socket))
         {
            fprintf(stderr, "accept() failed. (%d)\n",
                    GETSOCKETERRNO());
            return EXIT_FAILURE;
         }

         client->ssl = SSL_new(ctx);
         if (client->ssl == NULL)
         {
            fprintf(stderr, "SSL_new() failed.\n");
            return EXIT_FAILURE;
         }

         SSL_set_fd(client->ssl, client->socket);
         if (SSL_accept(client->ssl) != 1)
         {
            // SSL_get_error(client->ssl, SSL_accept(...));
            ERR_print_errors_fp(stderr);
            drop_client(client);
         }
         else
         {
            printf("New connection from %s.\n",
                   get_client_address(client));

            printf("SSL connection using %s\n",
                   SSL_get_cipher(client->ssl));
         }
      }

      struct client_info *client = clients;
      while (client != NULL)
      {
         client_info_t *nextClient = client->next;
         if (FD_ISSET(client->socket, &reads))
         {
            if (MAX_REQUEST_SIZE == client->received)
            {
               send_400(client);
               client = nextClient;
               continue;
            }

            int readCount = SSL_read(client->ssl,
                                     client->request + client->received,
                                     MAX_REQUEST_SIZE - client->received);
            if (readCount < 1)
            {
               printf("Unexpected disconnect from %s.\n",
                      get_client_address(client));
               drop_client(client);
            }
            else
            {
               client->received += readCount;
               client->request[client->received] = 0;
               char *query = strstr(client->request, "\r\n\r\n");
               if (query != NULL)
               {
                  *query = 0;
                  if (strncmp("GET /", client->request, 5) != 0)
                  {
                     send_400(client);
                  }
                  else
                  {
                     char *path = client->request + 4;
                     char *end_path = strstr(path, " ");
                     if (!end_path)
                     {
                        send_400(client);
                     }
                     else
                     {
                        *end_path = 0;
                        serve_resource(client, path);
                     }
                  }
               }
            }
         }

         client = nextClient;
      }
   }

   printf("\nClosing socket...\n");
   CLOSESOCKET(server);
   SSL_CTX_free(ctx);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}
