#include "projection_test.hpp"
#include <iostream>
#include "../../brux/main.hpp"
#include "../../brux/sprite.hpp"
#include "../../brux/graphics.hpp"
#include "../../api/sprites.hpp"
#include "../../api/input.hpp"
#include "../../api/graphics.hpp"
#include "../../api/sdl.hpp"
#include "../../math3/mesh3.hpp"
#include "../../math3/camera3.hpp"

ProjectionTest::ProjectionTest(){
    quit = false;
    std::cout << "instantiating game" << std::endl;
    camera = Camera3(
        Vector3(0.0f, 1.0f, 0.0f), //up
        Vector3(0.0f, 0.0f, -1.0f), //target
        Vector3(0.0f, 0.0f, 3.0f)); //position
    Mesh3 mesh;
    objects.push_back(mesh);
}

void ProjectionTest::Update(){
    if(BruxAPI::keyPress(k_escape)) quit = true;
    if(BruxAPI::keyDown(k_d)) camera.position.x += 0.01f;
    if(BruxAPI::keyDown(k_a)) camera.position.x -= 0.01f;
    if(BruxAPI::keyDown(k_w)) camera.position.z += 0.01f;
    if(BruxAPI::keyDown(k_s)) camera.position.z -= 0.01f;
    if(BruxAPI::keyDown(k_lshift)) camera.position.y += 0.01f;
    if(BruxAPI::keyDown(k_space)) camera.position.y -= 0.01f;
    for(auto &mesh : objects){
        mesh.RenderTriangles(camera);
    }
    xyUpdate();
    //std::cout << "this is updating, I think I'll make a StartGame function that has the game loop in it and calls this function" << std::endl;
}

void ProjectionTest::StartGame(){
    BruxAPI::setResolution(1600, 800);
    SDL_ShowCursor(1);
    test_sprite = BruxAPI::newSprite("../src/assets/Sprite-0001.png", 32, 32, 0, 0, 0, 0);
    while(!quit){
        ProjectionTest::Update();
    }
}

void ProjectionTest::Draw(){} //probably gonna remain unused