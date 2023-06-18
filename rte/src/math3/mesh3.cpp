#include "mesh3.hpp"
#include "matrix_multiplication3.hpp"
#include "vector3.hpp"
#include "matrix4x4.hpp"
#include "../api/sdl.hpp"
#include "../brux/graphics.hpp"
#include "../api/graphics.hpp"
#include "camera3.hpp"

Mesh3::Mesh3(){
    triangles.push_back(
        Triangle3(
            Vector3(0.0f, 0.5f,0.0f),
            Vector3(0.5f, 0.0f,0.0f),
            Vector3(0.5f, 0.5f,0.0f)
        )
    );
}

void
Mesh3::RenderTriangles(Camera3 _camera){

    Matrix4x4 point_at_mat;
    point_at_mat.CreatePointAt(_camera.target, _camera.up, _camera.position);

    Matrix4x4 this_mat;
    this_mat.CreateThisMatrix(_camera.position);

    Matrix4x4 look_at_mat;
    look_at_mat = Multiply4x4(point_at_mat, this_mat);

    Matrix4x4 trans_mat;
    trans_mat.CreateTranslation(_camera.position);

    Matrix4x4 proj_mat;
    proj_mat.CreateProjection((float)BruxAPI::screenH()/(float)BruxAPI::screenW(), 90.0f, 1000.0f, 0.1f);

    xySetDrawColor(0xFFFFFFFF);
    for(auto triangle : triangles){

        Triangle3 tri_l = MultiplyTriangle(triangle, this_mat);
        Triangle3 tri_pro = MultiplyTriangle(triangle, proj_mat);
        Triangle3 tri_s = DivideTriangleW(tri_pro);

        Vector3 offset_view(1.0f, 1.0f, 0.0f);

        tri_s.p1.x += 1.0f; tri_s.p1.y += 1.0f;
        tri_s.p2.x += 1.0f; tri_s.p2.y += 1.0f;
        tri_s.p3.x += 1.0f; tri_s.p3.y += 1.0f;

        tri_s.p1.x *= BruxAPI::screenW() * 0.5f; tri_s.p1.y *= BruxAPI::screenH() * 0.5f;
        tri_s.p2.x *= BruxAPI::screenW() * 0.5f; tri_s.p2.y *= BruxAPI::screenH() * 0.5f;
        tri_s.p3.x *= BruxAPI::screenW() * 0.5f; tri_s.p3.y *= BruxAPI::screenH() * 0.5f;

        
        BruxAPI::drawLine(tri_s.p1.x, tri_s.p1.y, tri_s.p2.x, tri_s.p2.y);
        BruxAPI::drawLine(tri_s.p2.x, tri_s.p2.y, tri_s.p3.x, tri_s.p3.y);
        BruxAPI::drawLine(tri_s.p3.x, tri_s.p3.y, tri_s.p1.x, tri_s.p1.y);
        

    }
}