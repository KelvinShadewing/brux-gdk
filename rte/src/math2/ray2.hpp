#ifndef RAY2_H
#define RAY2_H

#include "vector2.hpp"

class Ray2{
public:
    Vector2 p1;
    Vector2 p2;
    Ray2(Vector2 _p1, Vector2 _p2);
};

#endif