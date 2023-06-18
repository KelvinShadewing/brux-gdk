#ifndef MATRIX_4x4_H
#define MATRIX_4x4_H

enum MatrixType{
    EMPTY,
    IDENTITY,
    PROJECTION,
    POINT_AT,
    LOOK_AT,
    INVERSE
};

#include "vector3.hpp"

class Matrix4x4{
public:
    int matrix_type;
    float mat4x4[4][4];
    Matrix4x4(int _matrix_type = EMPTY): matrix_type{_matrix_type}{}
    void CreateEmpty();
    void CreateIdentity();
    void CreateProjection(float aspect_ratio, float field_of_view, float z_far, float z_near);
    void CreatePointAt(Vector3 _foward, Vector3 _up, Vector3 _position);
    void CreateLookAt(Vector3 _forward, Vector3 _up, Vector3 _position);
    void CreateInverse(Matrix4x4 _matrix);
    void CreateTranslation(Vector3 _position);
    void QuickInverse(Matrix4x4 _matrix);
    void CreateThisMatrix(Vector3 _position);
};

#endif