#include "matrix4x4.hpp"
#include <cmath>
#include <iostream>
#include "vector3_maths.hpp"

void
Matrix4x4::CreateEmpty(){
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            mat4x4[y][x] = 0.0f;
        }
    }
}

void
Matrix4x4::CreateProjection(float aspect_ratio, float field_of_view, float z_far, float z_near){
    CreateEmpty();
    mat4x4[0][0] = aspect_ratio * 1.0f/(std::tan(field_of_view * 0.5f / 180.0f * 3.141592f));
    mat4x4[1][1] = 1.0f/(std::tan(field_of_view * 0.5f / 180.0f * 3.141592f));
    mat4x4[2][2] = z_far / (z_far - z_near);
    mat4x4[2][3] = -z_far * z_near / (z_far - z_near);
    mat4x4[3][2] = 1.0f;
}

void
Matrix4x4::CreatePointAt(Vector3 _forward, Vector3 _up, Vector3 _position){
    CreateEmpty();
    Vector3 _right = CrossProduct(_forward, _up);
    mat4x4[0][0] = _right.x;
    mat4x4[0][1] = _right.y;
    mat4x4[0][2] = _right.z;
    mat4x4[1][0] = _up.x;
    mat4x4[1][1] = _up.y;
    mat4x4[1][2] = _up.z;
    mat4x4[2][0] = _forward.x;
    mat4x4[2][1] = _forward.y;
    mat4x4[2][2] = _forward.z;
    mat4x4[3][3] = 1.0f;

    /*for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            std::cout << mat4x4[y][x] << ", ";
        }
        std::cout << "\n";
    }*/
}

void
Matrix4x4::CreateLookAt(Vector3 _forward, Vector3 _up, Vector3 _position){
    CreateEmpty();

    Vector3 _right = CrossProduct(_forward, _up);

    mat4x4[0][0] = _forward.x;
    mat4x4[0][1] = _right.x;
    mat4x4[0][2] = _up.x;
    mat4x4[1][0] = _forward.y;
    mat4x4[1][1] = _right.y;
    mat4x4[1][2] = _up.y;
    mat4x4[2][0] = _forward.z;
    mat4x4[2][1] = _right.z;
    mat4x4[2][2] = _up.z;
    mat4x4[3][0] = -(_position.x * _forward.x + _position.y * _forward.y + _position.z * _forward.z);
    mat4x4[3][1] = -(_position.x * _right.x + _position.y * _right.y + _position.z * _right.z);
    mat4x4[3][2] = -(_position.x * _up.x + _position.y * _up.y + _position.z * _up.z);
    mat4x4[3][3] = 1.0f;
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            std::cout << mat4x4[y][x] << ", ";
        }
        std::cout << "\n";
    }
}

void
Matrix4x4::CreateTranslation(Vector3 _position){
    CreateEmpty();
    mat4x4[0][0] = 1.0f;
    mat4x4[1][1] = 1.0f;
    mat4x4[2][2] = 1.0f;
    mat4x4[3][3] = 1.0f;
    mat4x4[3][0] = _position.x;
    mat4x4[3][1] = _position.y;
    mat4x4[3][2] = _position.z;

    /*for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            std::cout << mat4x4[y][x] << ", ";
        }
        std::cout << "\n";
    }*/

}

void
Matrix4x4::CreateThisMatrix(Vector3 _position){
    CreateEmpty();
    mat4x4[0][0] = 1.0f;
    mat4x4[1][1] = 1.0f;
    mat4x4[2][2] = 1.0f;
    mat4x4[3][3] = 1.0f;
    mat4x4[3][3] = -_position.x;
    mat4x4[3][3] = -_position.y;
    mat4x4[3][3] = -_position.z;

    /*for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            std::cout << mat4x4[y][x] << ", ";
        }
        std::cout << "\n";
    }*/

}

void
Matrix4x4::QuickInverse(Matrix4x4 _matrix){
    Matrix4x4 out_matrix;

    mat4x4[0][0] = _matrix.mat4x4[0][0]; mat4x4[0][1] = _matrix.mat4x4[1][0];
    mat4x4[0][2] = _matrix.mat4x4[2][0]; mat4x4[0][3] = 0.0f;
    mat4x4[0][0] = _matrix.mat4x4[0][0]; mat4x4[0][1] = _matrix.mat4x4[1][0];
    mat4x4[0][2] = _matrix.mat4x4[2][0]; mat4x4[0][3] = 0.0f;

}