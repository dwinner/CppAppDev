#pragma once

#include "commonTypes.h"

void tweakSolution(memberType* member);

void initializeSolution(memberType* member);

unsigned int randInterval(unsigned int min, unsigned int max);

void computeEnergy(memberType* member);

/**
 * Копирование решения
 * @param dest Исходное решение
 * @param src  Назначенное решение
 */
void copySolution(memberType *dest, memberType * src);

/**
 * Отображение решения в виде шахматной доски
 * @param member Решение
 */
void emitSolution(memberType *member);
