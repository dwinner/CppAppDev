//
// Rules based system actions
//

#ifndef EXPERTSYSTEMS_RULEFIRE_H
#define EXPERTSYSTEMS_RULEFIRE_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "common.h"
#include "timers.h"

extern memoryElementType workingMemory[MAX_MEMORY_ELEMENTS];
extern ruleType ruleSet[MAX_RULES];

/**
 * @brief Find an empty slot in the working memory.
 * @return Empty slot index
 */
int findEmptyMemSlot(void);

/**
 * @brief Construct a fact from the current element, substituting the
 *  second argument if necessary.
 * @param new New element
 * @param old Old element
 * @param arg Argument
 */
void constructElement(char *new, const char *old, const char *arg);

/**
 * @brief Add a fact to the working memory.
 * @param mem Working memory
 * @return 1 if added, 0 otherwise
 */
int performAddCommand(char *mem);

/**
 * @brief Delete a fact from the working memory.
 * @param mem Working memory
 * @return 1 if removed, 0 otherwise
 */
int performDeleteCommand(char *mem);

/**
 * @brief Print an arbitrary string.
 * @param element Element
 * @return Always 1
 */
int performPrintCommand(const char *element);

/**
 * @brief Enable a timer, with a given expiration.
 * @param element element
 * @return Always 1
 */
int performEnableCommand(char *element);

/**
 * @brief In firing the rule, we perform all of the actions in the consequent
 *  section of the rule.
 * @param rule Rule index
 * @param arg Rule argument
 * @return Command result
 */
int fireRule(int rule, const char *arg);

#endif //EXPERTSYSTEMS_RULEFIRE_H
