#ifndef RECTANGLE_2_H
#define RECTANGLE_2_H

#include "vector2.hpp"

class Rectangle2{
public:
    Vector2 position;
    Vector2 size;
    int id;
    Rectangle2(Vector2 _position, Vector2 _size);
};

#endif