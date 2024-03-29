#include "ssl_network.h"

#if defined(_WIN32)
#include <conio.h>
#endif

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
   if (!ctx)
   {
      fprintf(stderr, "SSL_CTX_new() failed.\n");
      return EXIT_FAILURE;
   }

   if (argc < 3)
   {
      fprintf(stderr, "usage: tls_client hostname port\n");
      return EXIT_FAILURE;
   }

   printf("Configuring remote address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_socktype = SOCK_STREAM;
   struct addrinfo *peer_address;
   if (getaddrinfo(argv[1], argv[2], &hints, &peer_address))
   {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   printf("Remote address is: ");
   char address_buffer[100];
   char service_buffer[100];
   getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
               address_buffer, sizeof(address_buffer),
               service_buffer, sizeof(service_buffer),
               NI_NUMERICHOST);
   printf("%s %s\n", address_buffer, service_buffer);

   printf("Creating socket...\n");
   SOCKET socket_peer = socket(peer_address->ai_family,
                               peer_address->ai_socktype,
                               peer_address->ai_protocol);
   if (!ISVALIDSOCKET(socket_peer))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   printf("Connecting...\n");
   if (connect(socket_peer,
               peer_address->ai_addr, peer_address->ai_addrlen))
   {
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   freeaddrinfo(peer_address);

   SSL *ssl = SSL_new(ctx);
   if (ssl == NULL)
   {
      fprintf(stderr, "SSL_new() failed.\n");
      return EXIT_FAILURE;
   }

   SSL_set_fd(ssl, socket_peer);
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

   printf("Connected.\n");
   printf("To send data, enter text followed by enter.\n");

   while (1)
   {
      fd_set reads;
      FD_ZERO(&reads);
      FD_SET(socket_peer, &reads);
#if !defined(_WIN32)
      FD_SET(0, &reads);
#endif

      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 100000;
      if (select(socket_peer + 1, &reads, 0, 0, &timeout) < 0)
      {
         fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
         return EXIT_FAILURE;
      }

      if (FD_ISSET(socket_peer, &reads))
      {
         char read[4096];
         int bytes_received = SSL_read(ssl, read, 4096);
         if (bytes_received < 1)
         {
            printf("Connection closed by peer.\n");
            break;
         }

         printf("Received (%d bytes): %.*s",
                bytes_received,
                bytes_received, read);
      }

#if defined(_WIN32)
      if(_kbhit())
      {
#else
      if (FD_ISSET(0, &reads))
      {
#endif
         char read[4096];
         if (!fgets(read, 4096, stdin))
         {
            break;
         }

         printf("Sending: %s", read);
         int bytes_sent = SSL_write(ssl, read, (int) strlen(read));
         printf("Sent %d bytes.\n", bytes_sent);
      }
   }

   printf("Closing socket...\n");
   SSL_shutdown(ssl);
   CLOSESOCKET(socket_peer);
   SSL_free(ssl);
   SSL_CTX_free(ctx);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}
