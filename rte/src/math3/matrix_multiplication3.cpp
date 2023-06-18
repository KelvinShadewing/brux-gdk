#include "matrix_multiplication3.hpp"

#include "vector4.hpp"
#include "matrix4x4.hpp"
#include "triangle3.hpp"

Vector3 Multiply4x4(Vector3 vec, Matrix4x4 in_mat){
    Vector3 out_vec;
    out_vec.x = (
        vec.x * in_mat.mat4x4[0][0] + vec.y * in_mat.mat4x4[0][1] + vec.z * in_mat.mat4x4[0][2] + vec.w * in_mat.mat4x4[0][3]
    );
    out_vec.y = (
        vec.x * in_mat.mat4x4[1][0] + vec.y * in_mat.mat4x4[1][1] + vec.z * in_mat.mat4x4[1][2] + vec.w * in_mat.mat4x4[1][3]
    );
    out_vec.z = (
        vec.x * in_mat.mat4x4[2][0] + vec.y * in_mat.mat4x4[2][1] + vec.z * in_mat.mat4x4[2][2] + vec.w * in_mat.mat4x4[2][3]
    );
    out_vec.w = (
        vec.x * in_mat.mat4x4[3][0] + vec.y * in_mat.mat4x4[3][1] + vec.z * in_mat.mat4x4[3][2] + vec.w * in_mat.mat4x4[3][3]
    );
    return out_vec;
}

Triangle3
MultiplyTriangle(Triangle3 tri, Matrix4x4 _matrix){
    Vector3 p1 = Multiply4x4(tri.p1, _matrix);
    Vector3 p2 = Multiply4x4(tri.p2, _matrix);
    Vector3 p3 = Multiply4x4(tri.p3, _matrix);

    
    return Triangle3(
        p1, p2, p3
    );
}

Triangle3
DivideTriangleW(Triangle3 tri){
    Vector3 p1 = Vector3(tri.p1.x/tri.p1.w, tri.p1.y/tri.p1.w, tri.p1.z/tri.p1.w);
    Vector3 p2 = Vector3(tri.p2.x/tri.p2.w, tri.p2.y/tri.p2.w, tri.p2.z/tri.p2.w);
    Vector3 p3 = Vector3(tri.p3.x/tri.p3.w, tri.p3.y/tri.p3.w, tri.p3.z/tri.p3.w);

    
    return Triangle3(
        p1, p2, p3
    );
}

Matrix4x4
Multiply4x4(Matrix4x4 a, Matrix4x4 b){
    Matrix4x4 out_mat;

    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            out_mat.mat4x4[r][c] = a.mat4x4[r][0] * b.mat4x4[0][c] + a.mat4x4[r][1] * b.mat4x4[1][c] + a.mat4x4[r][2] * b.mat4x4[2][c] + a.mat4x4[r][3] * b.mat4x4[3][c];
    return out_mat;
}