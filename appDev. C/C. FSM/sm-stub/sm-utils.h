#ifndef SM_STUB_SM_UTILS_H
#define SM_STUB_SM_UTILS_H

#include "stub_fsm.h"

/**
 * @brief Gets a random number between 0 and limit inclusive.
 * @param limit limit number
 * @return random number between 0 and limit inclusive
 */
int rand_lim(int limit);

char* state_code_to_str(StateReturnCodeT state_code);

char* state_to_str(StateT state);

#endif //SM_STUB_SM_UTILS_H
