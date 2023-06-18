#ifndef MESH_3
#define MESH_3

#include <vector>

#include "triangle3.hpp"
#include "camera3.hpp"

class Mesh3{
public:
    std::vector<Triangle3> triangles;
    Mesh3();
    void RenderTriangles(Camera3 _camera);
};

#endif