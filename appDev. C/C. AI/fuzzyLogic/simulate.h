//
// Fuzzy Logic Simulated Battery Charge Controller
//

#ifndef FUZZYLOGIC_SIMULATE_H
#define FUZZYLOGIC_SIMULATE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fuzzy.h"
#include "mbrship.h"

#define getSRand()   ((float)rand() / (float)RAND_MAX)
#define getRand(x)   (int)((x) * getSRand())
#define MAX_LOADS   5

extern int chargeMode;
extern float voltage;
extern float temperature;
extern float timer;
extern const float load[MAX_LOADS];

/**
 * @brief Given temperature and voltage values, use the fuzzy logic
 *  membership functions and fuzzy operators to determine the
 *  charge mode.
 * @param aTimer Timer value
 */
void chargeControl(float *aTimer);

double charge(int aTemperature);

int simulate(void);

#endif //FUZZYLOGIC_SIMULATE_H
