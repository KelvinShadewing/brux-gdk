#ifndef MENU_ENTRY_H
#define MENU_ENTRY_H
#include <functional>
#include <vector>
#include "../../math2/ray2.hpp"

class MenuEntry{
public:
    std::function<void(std::vector<Ray2> &lines)> Spawn;
    int icon;
    MenuEntry(std::function<void(std::vector<Ray2> &lines)> _spawn, int _icon);
    void Draw(int _object, int _index);
    void HandleSelected(int _object, int _index);
};

#endif