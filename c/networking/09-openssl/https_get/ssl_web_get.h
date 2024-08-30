//
// Created by ubuntu on 12/27/22.
//

#ifndef HTTPS_GET_SSL_WEB_GET_H
#define HTTPS_GET_SSL_WEB_GET_H

#include "ssl_network.h"

/**
 * @brief Timeout for multiplexing connection
 */
#define TIMEOUT 5.0

/**
 * @brief Buffer size (i.e. for request)
 */
#define BUFFER_SIZE 2048

/**
 * @brief Buffer for address storage
 */
#define ADDR_BUFFER 100

/**
 * @brief Parses URL into hostname, port, path
 *
 * @param aUrl URL to be parsed
 * @param aHostname Host name as out
 * @param aPort Port as out
 * @param aPathPath Path as out
 */
void parse_url(char *aUrl, char **aHostname, char **aPort, char **aPath);

/**
 * @brief Sends a request through the SSL connection
 *
 * @param anSsl SSL connection
 * @param aHostname Host name
 * @param aPort Port
 * @param aPath Path
 */
void send_request(SSL *anSsl, char *aHostname, char *aPort, char *aPath);

/**
 * @brief Connects to a host
 *
 * @param aHostname Host name
 * @param aPort Port
 * @return Valid socket's fd
 */
SOCKET connect_to_host(char *aHostname, char *aPort);

#endif //HTTPS_GET_SSL_WEB_GET_H
