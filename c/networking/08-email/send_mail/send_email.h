//
// Created by ubuntu on 12/21/22.
//

#ifndef SEND_MAIL_SEND_EMAIL_H
#define SEND_MAIL_SEND_EMAIL_H

/**
 * @brief Max input size
 */
#include "network.h"

#define MAX_INPUT 512

/**
 * @brief Max response size
 */
#define MAX_RESPONSE 1024

/**
 * @brief Max buffer size
 */
#define MAX_BUFFER_SIZE 1024

/**
 * @brief Gets an input into the buffer
 * @param aPrompt Prompt for a user
 * @param aBuffer Buffer for inputting
 */
void get_input(const char *aPrompt, char *aBuffer);

/**
 * @brief Sends command to the server
 * @param aServer Server socket
 * @param aText Text to be sent
 * @param ... Variable args for formatted text
 */
void send_format(SOCKET aServer, const char *aText, ...);

/**
 * @brief Parses response
 * @param response Response to be parsed
 * @return Response code or 0 if failed
 */
int parse_response(const char *response);

/**
 * @brief Waits on response
 * @param aServer Server socket
 * @param anExpectingCode Expecting code
 */
void wait_on_response(SOCKET aServer, int anExpectingCode);

/**
 * @brief Connects to a host
 * @param hostname Host name
 * @param port Port
 * @return Server socket
 */
SOCKET connect_to_host(const char *hostname, const char *port);

#endif //SEND_MAIL_SEND_EMAIL_H
