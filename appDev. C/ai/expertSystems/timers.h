//
// Rules based system timer routines
//

#ifndef EXPERTSYSTEMS_TIMERS_H
#define EXPERTSYSTEMS_TIMERS_H

#include <stdio.h>
#include "common.h"
#include "ruleFire.h"

extern timerType timers[MAX_TIMERS];

/**
 * @brief Fire the defined timer. This involves adding a '(timer-triggered x)'
 *  fact to the working memory, with x='expired timer'.
 * @param timerIndex Timer index
 * @return Result code of adding command
 */
int fireTimer(int timerIndex);

/**
 * @brief Activate a timer with a given expiration time.
 * @param index Timer index
 * @param expiration Expiration
 */
void startTimer(int index, int expiration);

/**
 * @brief Process the active timer list, upon finding an expired timer,
 *  fire it.
 */
void processTimers(void);

#endif //EXPERTSYSTEMS_TIMERS_H
