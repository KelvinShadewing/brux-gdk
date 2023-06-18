#include "ray_vs_plane.hpp"
#include "vector3.hpp"
#include "triangle3.hpp"
#include <cmath>
#include "vector3_maths.hpp"

float RayVsPlane(Vector3 p1, Vector3 p2, Vector3 q1, Vector3 q2, Vector3 q3){
    Vector3 n = CrossProduct(q1, q2, q3);
    n = Vector3{
        n.x/std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z),
        n.y/std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z),
        n.z/std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z)
        };
    
    float a = n.x *(p2.x - p1.x) + n.y*(p2.y - p1.y) + n.z *(p2.z - p1.z);
    float b = p1.x * n.x + p1.y * n.y + p1.z * n.z;
    float c = q1.x * n.x + q1.y * n.y + q1.z * n.z;
    
    //0 = at + b - c
    // -(b-c)/a = t
    float t = -(b-c)/a;


    return t;
}

float RayVsPlane(Ray3 ray, Triangle3 tri){
    Vector3 n = CrossProduct(tri.p1, tri.p2, tri.p3);
    
    float a = n.x *(ray.p2.x - ray.p1.x) + n.y*(ray.p2.y - ray.p1.y) + n.z *(ray.p2.z - ray.p1.z);
    float b = ray.p1.x * n.x + ray.p1.y * n.y + ray.p1.z * n.z;
    float c = tri.p1.x * n.x + tri.p1.y * n.y + tri.p1.z * n.z;
    
    //0 = at + b - c
    // -(b-c)/a = t
    float t = -(b-c)/a;


    return t;
}