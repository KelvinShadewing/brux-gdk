#include "menu_entry.hpp"
#include <functional>
#include "../../api/sprites.hpp"
#include "../../api/graphics.hpp"
#include <iostream>

MenuEntry::MenuEntry(std::function<void(std::vector<Ray2> &lines)> _spawn, int _icon): Spawn{_spawn}, icon{_icon}{}

void
MenuEntry::HandleSelected(int _object, int _index){
}

void
MenuEntry::Draw(int _object, int _index){
    if((_object == _index)){
        BruxAPI::drawSpriteEx(icon, 0, BruxAPI::screenW()-32-3, 32*_index, 0, 0, 1, 1, 1);
    }
    else{
        BruxAPI::drawSpriteEx(icon, 0, BruxAPI::screenW()-32-3, 32*_index, 0, 0, 1, 1, 0.5f);
    }

    
}