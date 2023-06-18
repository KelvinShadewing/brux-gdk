#ifndef MATRIX_MULTIPLICATION_3_H
#define MATRIX_MULTIPLICATION_3_H
#include "matrix4x4.hpp"
#include "vector4.hpp"
#include "triangle3.hpp"

Vector3 Multiply4x4(Vector3 vec, Matrix4x4 in_mat); //needs Vector4
Matrix4x4 Multiply4x4(Matrix4x4 a, Matrix4x4 b);
Triangle3 MultiplyTriangle(Triangle3 tri, Matrix4x4 _matrix);
Triangle3 DivideTriangleW(Triangle3 tri);
#endif