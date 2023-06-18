#ifndef VECTOR_FEATURES_H
#define VECTOR_FEATURES_H
#include "collision_info.hpp"

struct Ray2;

CollisionInfo RayVsLine(Ray2 ray, Ray2 line);
bool LineDetected(CollisionInfo _info);

#endif