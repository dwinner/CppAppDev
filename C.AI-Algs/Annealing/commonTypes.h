#pragma once

/**
 * Размер доски
 */
#define MAX_LENGTH 30

/**
 * Кодировка задачи о ферзях
 */
typedef int solutionType[MAX_LENGTH];

/**
 * Решение задачи
 */
typedef struct 
{
	solutionType solution;
	float energy;
} memberType;

/* Параметры алгоритма */
#define INITIAL_TEMPERATURE 30.0
#define FINAL_TEMPERATURE 0.5
#define ALPHA 0.98	/* Геометрическое охлаждение */
#define STEPS_PER_CHANGE 100	/* Кол-во итераций после каждого изменения температуры */
