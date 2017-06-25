#pragma once

#define MAX_LENGTH 30

typedef int solutionType[MAX_LENGTH];

typedef struct 
{
	solutionType solution;
	float energy;
} memberType;

#define INITIAL_TEMPERATURE 30.0
#define FINAL_TEMPERATURE 0.5
#define ALPHA 0.98
#define STEPS_PER_CHANGE 100
