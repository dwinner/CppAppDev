//
// Rules based system matcher
//

#ifndef EXPERTSYSTEMS_RULECHK_H
#define EXPERTSYSTEMS_RULECHK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "ruleFire.h"

extern memoryElementType workingMemory[MAX_MEMORY_ELEMENTS];
extern ruleType ruleSet[MAX_RULES];
extern memoryElementType *chain;

/**
 * @brief Search the working memory for the two passed terms.
 * @param term1 Term #1
 * @param term2 Term #2
 * @return 1 if found, 0 otherwise
 */
int searchWorkingMemory(char *term1, char *term2);

/**
 * @brief Create a chain second terms from working memory where the first terms
 *  match, and the second term in the antecedent is the '?' symbol.
 * @param element Element
 */
void addToChain(char *element);

/**
 * @brief Try to match all of the antecedents of a rule to facts in working
 *  memory. This includes matching antecedent rules with '?' terms
 *  with facts from working memory.
 * @param rule Rule index
 * @param arg Argument
 * @return Search result
 */
int checkPattern(int rule, char *arg);

/**
 * @brief Check to see if the rule will fire, based upon the facts in
 *  working memory.
 * @param rule Rule index
 * @return Firing result (1 or 0)
 */
int checkRule(int rule);

#endif //EXPERTSYSTEMS_RULECHK_H
