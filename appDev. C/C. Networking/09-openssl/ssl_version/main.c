/**
 * gcc main.c -o ssl_version -lcrypto
 */

#include <openssl/ssl.h>

int main(int argc, char *argv[])
{
   printf("OpenSSL version: %s\n", OpenSSL_version(SSLEAY_VERSION));

   return EXIT_SUCCESS;
}
