#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "vector3.hpp"

class Camera3{
public:
    
    Vector3 up;
    Vector3 target;
    Vector3 position;
    float yaw;
    Camera3() = default;
    Camera3(Vector3 _up, Vector3 _target, Vector3 _position): up{_up}, target{_target}, position{_position}, yaw{0.0f}{}
};

#endif