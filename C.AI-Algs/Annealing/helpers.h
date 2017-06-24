#pragma once

#include "commonTypes.h"

/**
 * \brief Замена решения
 * \param member решение
 */
void tweakSolution(memberType *member);

/**
 * \brief Инициализация решения
 * \param member решение
 */
void initializeSolution(memberType *member);

unsigned int randInterval(unsigned int min, unsigned int max);

/**
 * \brief Оценка решения
 * \param member Решение
 */
void computeEnergy(memberType *member);
