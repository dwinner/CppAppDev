#ifndef WEBSERVERDEMO_WEB_SRV_API_H
#define WEBSERVERDEMO_WEB_SRV_API_H

#include "network.h"

/**
 * @brief Mime type array length
 */
#define MIME_TYPE_LEN 14

/**
 * @brief Maximum concurrent connections accepted
 */
#define CONNECTION_THRESHOLD 10

/**
 * @brief Maximum request size
 */
#define MAX_REQUEST_SIZE 2047

/**
 * @brief Buffer size for making request/response operations
 */
#define BUFFER_SIZE 1024

/**
 * @brief Buffer length
 */
#define BUFFER_LEN 100

/**
 * @brief Max path length
 */
#define MAX_PATH_LEN 100

/**
 * @brief Path buffer length
 */
#define PATH_BUFFER 128

/**
 * @brief Map struct for Extension => Mime type
 */
typedef struct MimeMap
{
   /**
    * Extension
    */
   char *extension;

   /**
    * Mime type
    */
   char *mime_type;
} MimeMapT;

/**
 * @brief POD for client information
 */
typedef struct ClientInfo
{
   /**
    * Address length
    */
   socklen_t address_length;

   /**
    * Address storage
    */
   struct sockaddr_storage address;

   /**
    * Client socket
    */
   SOCKET socket;

   /**
    * Request content
    */
   char request[MAX_REQUEST_SIZE + 1];

   /**
    * Number of received bytes
    */
   int received;

   /**
    * Next available client information
    */
   struct ClientInfo *next;
} ClientInfoT;

extern ClientInfoT *clients;

/**
 * @brief Returns a content type dependin on a aPath
 * @param aPath Path to a file
 * @return Content type
 * @details i.e. ".css" => "text/css", etc.
 */
const char *get_content_type(const char *aPath);

/**
 * @brief Creates a connected socket
 * @param aHost Host
 * @param aPort Port
 * @return Valid socket descriptor, or fails in the case of any error
 */
SOCKET create_socket(const char *aHost, const char *aPort);

/**
 * @brief Gets connected client's information
 * @param aClientSocket Client's socket
 * @return Existing or just created client information
 */
ClientInfoT *get_client(SOCKET aClientSocket);

/**
 * @brief Drops the connected client
 * @param clientInfo Client information
 */
void drop_client(ClientInfoT *clientInfo);

/**
 * @brief Gets client's address
 * @param aClientInfo Client information
 * @return Client's address
 */
const char *get_client_address(ClientInfoT *aClientInfo);

/**
 * @brief Waits on server's socket
 * @param aServerSocket Server's socket
 * @return Ready to read fd_set descriptors
 */
fd_set wait_on_clients(SOCKET aServerSocket);

/**
 * @brief Sends Bad request to client
 * @param clientInfo Client information
 */
void send_400(ClientInfoT *clientInfo);

/**
 * @brief Sends Not Found to client
 * @param clientInfo Client information
 */
void send_404(ClientInfoT *clientInfo);

/**
 * @brief Serves a file resource by a path
 * @param aClientInfo Client information
 * @param aPath Relative path
 */
void serve_resource(ClientInfoT *aClientInfo, const char *aPath);

#endif // WEBSERVERDEMO_WEB_SRV_API_H
