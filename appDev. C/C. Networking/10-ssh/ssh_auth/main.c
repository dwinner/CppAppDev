#include "ssh_network.h"

int main(int argc, char *argv[])
{
   if (argc < 4)
   {
      fprintf(stderr, "Usage: ssh_auth hostname port user\n");
      return EXIT_FAILURE;
   }

   const char *hostname = argv[1];
   int port = atol(argv[2]);
   const char *user = argv[3];

   ssh_session ssh = ssh_new();
   if (ssh == NULL)
   {
      fprintf(stderr, "ssh_new() failed.\n");
      return EXIT_FAILURE;
   }

   ssh_options_set(ssh, SSH_OPTIONS_HOST, hostname);
   ssh_options_set(ssh, SSH_OPTIONS_PORT, &port);
   ssh_options_set(ssh, SSH_OPTIONS_USER, user);

   int ret = ssh_connect(ssh);
   if (ret != SSH_OK)
   {
      fprintf(stderr, "ssh_connect() failed.\n%s\n", ssh_get_error(ssh));
      return -1;
   }

   printf("Connected to '%s' on port %d.\n", hostname, port);
   printf("Banner:\n%s\n", ssh_get_serverbanner(ssh));

   ssh_key key;
   if (ssh_get_server_publickey(ssh, &key) != SSH_OK)
   {
      fprintf(stderr, "ssh_get_server_publickey() failed.\n%s\n",
              ssh_get_error(ssh));
      return -1;
   }

   unsigned char *hash;
   size_t hash_len;
   if (ssh_get_publickey_hash(key, SSH_PUBLICKEY_HASH_SHA1,
                              &hash, &hash_len) != SSH_OK)
   {
      fprintf(stderr, "ssh_get_publickey_hash() failed.\n%s\n",
              ssh_get_error(ssh));
      return -1;
   }

   printf("Host public key hash:\n");
   ssh_print_hash(SSH_PUBLICKEY_HASH_SHA1, hash, hash_len);

   ssh_clean_pubkey_hash(&hash);
   ssh_key_free(key);

   printf("Checking ssh_session_is_known_server()\n");
   enum ssh_known_hosts_e known = ssh_session_is_known_server(ssh);
   switch (known)
   {
      case SSH_KNOWN_HOSTS_OK:
         printf("Host Known.\n");
         break;

      case SSH_KNOWN_HOSTS_CHANGED:
         printf("Host Changed.\n");
         break;

      case SSH_KNOWN_HOSTS_OTHER:
         printf("Host Other.\n");
         break;

      case SSH_KNOWN_HOSTS_UNKNOWN:
         printf("Host Unknown.\n");
         break;

      case SSH_KNOWN_HOSTS_NOT_FOUND:
         printf("No host file.\n");
         break;

      case SSH_KNOWN_HOSTS_ERROR:
         printf("Host error. %s\n", ssh_get_error(ssh));
         return EXIT_FAILURE;

      default:
         printf("Error. Known: %d\n", known);
         return EXIT_FAILURE;
   }

   if (known == SSH_KNOWN_HOSTS_CHANGED ||
       known == SSH_KNOWN_HOSTS_OTHER ||
       known == SSH_KNOWN_HOSTS_UNKNOWN ||
       known == SSH_KNOWN_HOSTS_NOT_FOUND)
   {
      printf("Do you want to accept and remember this host? Y/N\n");
      char answer[10];
      fgets(answer, sizeof(answer), stdin);
      if (answer[0] != 'Y' && answer[0] != 'y')
      {
         return EXIT_SUCCESS;
      }

      ssh_session_update_known_hosts(ssh);
   }

   printf("Password: ");
   char password[128];
   fgets(password, sizeof(password), stdin);
   password[strlen(password) - 1] = 0;

   if (ssh_userauth_password(ssh, 0, password) != SSH_AUTH_SUCCESS)
   {
      fprintf(stderr, "ssh_userauth_password() failed.\n%s\n",
              ssh_get_error(ssh));
      return EXIT_SUCCESS;
   }
   else
   {
      printf("Authentication successful!\n");
   }

   ssh_disconnect(ssh);
   ssh_free(ssh);

   return EXIT_SUCCESS;
}
