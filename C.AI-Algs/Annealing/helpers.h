#pragma once

#include "commonTypes.h"

/**
 * \brief ������ �������
 * \param member �������
 */
void tweakSolution(memberType *member);

/**
 * \brief ������������� �������
 * \param member �������
 */
void initializeSolution(memberType *member);

unsigned int randInterval(unsigned int min, unsigned int max);

/**
 * \brief ������ �������
 * \param member �������
 */
void computeEnergy(memberType *member);
