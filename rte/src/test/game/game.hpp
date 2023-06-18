#ifndef GAME
#define GAME

#include <string>

class Game{
public:
    const int k_escape = 41;
    std::string app_name;
    bool quit;
    int test_sprite;
    Game();
    void StartGame();
    void Update();

    void Draw(); //unnecessary


};

#endif