#include "ssl_network.h"

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
      fprintf(stderr, "usage: tls_get_cert hostname port\n");
      return 1;
   }

   char *hostname = argv[1];
   char *port = argv[2];

   printf("Configuring remote address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_socktype = SOCK_STREAM;
   struct addrinfo *peer_address;
   if (getaddrinfo(hostname, port, &hints, &peer_address))
   {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
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
   SOCKET server = socket(peer_address->ai_family,
                          peer_address->ai_socktype,
                          peer_address->ai_protocol);
   if (!ISVALIDSOCKET(server))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   printf("Connecting...\n");
   if (connect(server,
               peer_address->ai_addr, peer_address->ai_addrlen))
   {
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   freeaddrinfo(peer_address);

   printf("Connected.\n\n");

   SSL *ssl = SSL_new(ctx);
   if (!ssl)
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
   if (!cert)
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
