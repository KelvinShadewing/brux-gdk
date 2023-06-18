#ifndef PLAYGROUND
#define PLAYGROUND

#include <string>
#include "editor.h"

class Playground{
public:
    const int k_escape = 41;
    std::string app_name;
    Editor editor;
    bool quit;
    int test_sprite;
    Playground();
    void StartGame();
    void Update();

    void Draw(); //unnecessary


};

#endif