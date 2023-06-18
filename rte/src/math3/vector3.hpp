#ifndef VECTOR_3_H
#define VECTOR_3_H


class Vector3{
public:
    float x;
    float y;
    float z;
    float w;
    Vector3() = default;
    Vector3(float _x, float _y, float _z, float _w = 1.0f) : x{_x}, y{_y}, z{_z}, w{_w}{}
    float Magnitude();
    Vector3 Normalize();
};

#endif