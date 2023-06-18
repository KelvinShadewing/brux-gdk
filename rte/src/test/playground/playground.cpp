#include "playground.hpp"
#include <iostream>
#include "../../brux/main.hpp"
#include "../../brux/sprite.hpp"
#include "../../brux/graphics.hpp"
#include "../../api/sprites.hpp"
#include "../../api/input.hpp"
#include "../../api/graphics.hpp"
#include "../../math2/ray2.hpp"
#include "../../math2/vector2.hpp"
#include "../../api/sdl.hpp"
#include "../../math2/vector_features.hpp"

Playground::Playground(){
    quit = false;
    std::cout << "instantiating game" << std::endl;
}

void Playground::Update(){
    
    Ray2 ray(Vector2(50.0f, 50.0f), Vector2(BruxAPI::mouseX(), BruxAPI::mouseY()));

    /*if(RayVsLine(ray, line) <= 1.0f && RayVsLine(ray, line) >= 0.0f){
        xySetDrawColor(0xFF00FFFF);
    }*/

    editor.Input();

    if(BruxAPI::keyPress(k_escape)) quit = true;

    xySetDrawColor(0xFFFFFFFF);
    BruxAPI::drawLine(ray.p1.x, ray.p1.y, ray.p2.x, ray.p2.y);

    for(auto &line : editor.lines){
        xySetDrawColor(0xFFFFFFFF);
        if(LineDetected(RayVsLine(ray, line))) xySetDrawColor(0xFF00FFFF);
        BruxAPI::drawLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y);
    }
    
    editor.Draw();
    
    xyUpdate();
    
    //std::cout << "this is updating, I think I'll make a StartGame function that has the game loop in it and calls this function" << std::endl;
}

void Playground::StartGame(){
    BruxAPI::setResolution(1600, 800);
    SDL_ShowCursor(1);
    test_sprite = BruxAPI::newSprite("../src/assets/Sprite-0001.png", 32, 32, 0, 0, 0, 0);
    while(!quit){
        Playground::Update();
    }
}

void Playground::Draw(){} //probably gonna remain unused