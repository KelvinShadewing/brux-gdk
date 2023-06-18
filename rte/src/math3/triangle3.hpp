#ifndef TRIANGLE_3_H
#define TRIANGLE_3_H

#include "vector3.hpp"

class Triangle3{
public:
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;
    Triangle3(
        Vector3 _p1,
        Vector3 _p2,
        Vector3 _p3) :
        p1{_p1},
        p2{_p2},
        p3{_p3}{}
};

#endif