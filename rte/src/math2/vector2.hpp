#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2{
public:
    float x;
    float y;
    Vector2() = default;
    Vector2(float _x, float _y) : x{_x}, y{_y}{}
    float Magnitude();
    Vector2 Normalize();
};

#endif