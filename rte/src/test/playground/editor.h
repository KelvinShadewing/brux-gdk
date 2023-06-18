#ifndef EDITOR
#define EDITOR
#include "../../math2/ray2.hpp"
#include <vector>
#include "menu_entry.hpp"
#include "asset_manager.hpp"
#include "line_tool.hpp"

enum Objects{
    LINE,
    RAY,
    CIRCLE
};

enum State{
    PLACING_LINE,
    PLACE
};

class Editor{
public:
    LineTool line_tool;

    std::vector <MenuEntry> menu;
    int state;
    int object;
    AssetManager assets;
    std::vector<Ray2> lines; 
    Editor();
    void Input();
    void HandleMousePress(int _x, int _y);
    void Draw();
};

#endif