#pragma once

#include "commonTypes.h"

void tweakSolution(memberType* member);

void initializeSolution(memberType* member);

unsigned int randInterval(unsigned int min, unsigned int max);

void computeEnergy(memberType* member);

/**
 * ����������� �������
 * @param dest �������� �������
 * @param src  ����������� �������
 */
void copySolution(memberType *dest, memberType * src);

/**
 * ����������� ������� � ���� ��������� �����
 * @param member �������
 */
void emitSolution(memberType *member);
