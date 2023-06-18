#ifndef COLLISION_INFO_H
#define COLLISION_INFO_H
#include "ray2.hpp"
#include "vector2.hpp"

class CollisionInfo{
public:
    float ray_time;
    float line_time;
    Ray2 line;
    Vector2 normal;
    CollisionInfo(
        float _ray_time,
        float _line_time,
        Ray2 _line) :
        ray_time{_ray_time}, line_time{_line_time}, line{_line}{}
};

#endif