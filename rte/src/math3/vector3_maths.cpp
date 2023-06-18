#include "vector3_maths.hpp"
#include "vector3.hpp"

Vector3 CrossProduct(Vector3 q1, Vector3 q2, Vector3 q3){
    Vector3 a = {q2.x - q1.x, q2.y - q1.y, q2.z - q1.z};
    Vector3 b = {q3.x - q1.x, q3.y - q1.y, q3.z - q1.z};
    Vector3 c = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
        };
    return c;
}

Vector3 CrossProduct(Vector3 a, Vector3 b){
    //v1(up) x v2(foward)
    Vector3 c = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
        };
    return c;
}