//
// Created by ubuntu on 12/27/22.
//

#ifndef HTTPS_SERVER_SSL_WEB_SRV_H
#define HTTPS_SERVER_SSL_WEB_SRV_H

#include "ssl_network.h"

#define MAX_REQUEST_SIZE 2047

#define BSIZE 1024

/**
 * @brief Client information
 */
typedef struct client_info
{
   socklen_t address_length;
   struct sockaddr_storage address;
   SOCKET socket;
   SSL *ssl;
   char request[MAX_REQUEST_SIZE + 1];
   int received;
   struct client_info *next;
} client_info_t;

/**
 * @brief clients being served
 */
extern client_info_t *clients;

/**
 * @brief Gets content type based on a path extension
 * @param aPath Path
 * @return Content type
 */
const char *get_content_type(const char *aPath);

/**
 * Creates server socket
 *
 * @param aHost Host
 * @param aPort Port
 * @return Server's socket or exists with error message
 */
SOCKET create_socket(const char *aHost, const char *aPort);

/**
 * Gets client information
 * @param aSocket Client's socket
 * @return Existing/Just created client information
 */
client_info_t *get_client(SOCKET aSocket);

/**
 * Drops client
 * @param aClient Client to drop
 */
void drop_client(client_info_t *aClient);

/**
 * Gets a client's address
 * @param aClient Client information
 * @return Client's address
 */
const char *get_client_address(client_info_t *aClient);

/**
 * Waits for a connected client
 * @param aServerSocket Server's socket
 * @return fd set updated for read-ready
 */
fd_set wait_on_clients(SOCKET aServerSocket);

/**
 * Sends Bad request to a client
 * @param aClient Client
 */
void send_400(client_info_t *aClient);

/**
 * Sends Not found to a client
 * @param aClient Client
 */
void send_404(client_info_t *aClient);

/**
 * Serves resource
 * @param aClient Client
 * @param aPath Path
 */
void serve_resource(client_info_t *aClient, const char *aPath);

#endif //HTTPS_SERVER_SSL_WEB_SRV_H
