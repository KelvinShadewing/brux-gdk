#include "vector_features.hpp"
#include "vector2.hpp"
#include "ray2.hpp"
#include "collision_info.hpp"

CollisionInfo RayVsLine(Ray2 ray, Ray2 line){
    
    Vector2 a = line.p1;
    Vector2 b = Vector2{line.p2.x - line.p1.x, line.p2.y - line.p1.y};
    Vector2 c = ray.p1;
    Vector2 d = Vector2{ray.p2.x - ray.p1.x, ray.p2.y - ray.p1.y};
    
    float h = (d.x * b.y - d.y * b.x);

    float t1 = (a.x * b.y - a.y * b.x - c.x * b.y + c.y * b.x)/h;
    float t2 = (c.x * d.y - c.y * d.x - a.x * d.y + a.y * d.x)/-h;

    return CollisionInfo(t1, t2, line);
}

bool LineDetected(CollisionInfo _info){
    if(_info.ray_time >= 0.0f && _info.ray_time <= 1.0f && _info.line_time >= 0.0f && _info.line_time <= 1.0f) return true;
    return false;
}