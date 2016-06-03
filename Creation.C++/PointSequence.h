//
// Created by DennyByDenny on 03.06.2016.
//

#ifndef CREATION_C_POINTSEQUENCE_H
#define CREATION_C_POINTSEQUENCE_H


#include <bits/stl_bvector.h>

class PointSequence
{
public:
    PointSequence(std::initializer_list<double> args);

    void dumpPoints() const;

protected:
    std::vector<double> points;
};


#endif //CREATION_C_POINTSEQUENCE_H
