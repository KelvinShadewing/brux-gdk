#ifndef RAY_3_H
#define RAY_3_H

#include "vector3.hpp"

class Ray3{
public:
    Vector3 p1;
    Vector3 p2;
    Ray3(
        Vector3 _p1,
        Vector3 _p2) :
        p1{_p1},
        p2{_p2}{}
};

#endif