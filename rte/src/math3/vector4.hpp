#ifndef VECTOR_4_H
#define VECTOR_4_H

class Vector4{
public:
    float x;
    float y;
    float z;
    float w;
    Vector4() = default;
    Vector4(float _x, float _y, float _z, float _w = 1) : x{_x}, y{_y}, z{_z}, w{_w}{}
    float Magnitude();
    Vector4 Normalize();
};

#endif