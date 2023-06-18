#include "game.hpp"
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

Game::Game(){
    quit = false;
    std::cout << "instantiating game" << std::endl;
}

void Game::Update(){
    xySetDrawColor(0xFFFFFFFF);
    Ray2 ray(Vector2(50.0f, 50.0f), Vector2(BruxAPI::mouseX(), BruxAPI::mouseY()));

    Ray2 line(Vector2(0.0f, 600.0f), (Vector2(800.0f, 20.0f)));

    /*if(RayVsLine(ray, line) <= 1.0f && RayVsLine(ray, line) >= 0.0f){ // WARNING OUTDATED USAGE //
        xySetDrawColor(0xFF00FFFF);
    }*/

    if(BruxAPI::keyPress(k_escape)) quit = true;

    BruxAPI::drawLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y);
    BruxAPI::drawLine(ray.p1.x, ray.p1.y, ray.p2.x, ray.p2.y);
    xyUpdate();
    //std::cout << "this is updating, I think I'll make a StartGame function that has the game loop in it and calls this function" << std::endl;
}

void Game::StartGame(){
    BruxAPI::setResolution(1600, 800);
    SDL_ShowCursor(1);
    test_sprite = BruxAPI::newSprite("../src/assets/Sprite-0001.png", 32, 32, 0, 0, 0, 0);
    while(!quit){
        Game::Update();
    }
}

void Game::Draw(){} //probably gonna remain unused