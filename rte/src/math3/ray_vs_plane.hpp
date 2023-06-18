#ifndef RAY_VS_PLANE_H
#define RAY_VS_PLANE_H

#include "vector3.hpp"
#include "ray3.hpp"
#include "triangle3.hpp"

Vector3 CrossProduct(Vector3 q1, Vector3 q2, Vector3 q3);

float RayVsPlane(Vector3 p1, Vector3 p2, Vector3 q1, Vector3 q2, Vector3 q3);
float RayVsPlane(Ray3 ray, Triangle3 tri);

#endif