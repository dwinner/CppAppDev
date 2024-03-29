//
// Rules based system parser
//

#ifndef EXPERTSYSTEMS_PARSER_H
#define EXPERTSYSTEMS_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#define MAX_FILE_SIZE   16384

extern memoryElementType workingMemory[MAX_MEMORY_ELEMENTS];
extern ruleType ruleSet[MAX_RULES];
extern int ruleIndex;

/**
 * @brief Skip the white space (in the context of rules grammar).
 * @param block Char block
 * @return Modified block
 */
char *skipWhiteSpace(char *block);

/**
 * @brief Parse a single consequent or antecedent from the file.
 * @param block Char block
 * @param met Memory element type
 * @return Char block
 */
char *parseElement(char *block, memoryElementType **met);

/**
 * @brief Parse an antecedent from the file.
 * @param block Char block
 * @param rule Rule type
 * @return Char block
 */
char *parseAntecedent(char *block, ruleType *rule);

/**
 * @brief Parse a consequent from the file.
 * @param block Char block
 * @param rule Rule type
 * @return Char block
 */
char *parseConsequent(char *block, ruleType *rule);

/**
 * @brief Parse the rules file.  This function parses the high level elements
 *  of the file, leaving parsing the antecedent and consequents to other
 *  functions.
 * @param filename file name
 * @return -1 if something went wrong, 0 if everything is fine
 */
int parseFile(char *filename);

#endif //EXPERTSYSTEMS_PARSER_H
