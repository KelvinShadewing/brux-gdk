#include "../../api/input.hpp"
#include "editor.h"
#include "menu_entry.hpp"
#include <iostream>
#include <vector>
#include "../../math2/ray2.hpp"
#include "../../math2/vector2.hpp"

Editor::Editor(){
    assets.AddSprite("icon_ray", "../src/test/playground/assets/line_icon.png", 32, 32);
    assets.AddSprite("icon_circle", "../src/test/playground/assets/ray_icon.png", 32, 32);
    assets.AddSprite("icon_line", "../src/test/playground/assets/circle_icon.png", 32, 32);
    object = 0;
    menu.push_back(
        MenuEntry(
            [](std::vector<Ray2> &lines){lines.push_back(
                    Ray2(
                        Vector2(0.0f, 0.0f),
                        Vector2(BruxAPI::mouseX(), BruxAPI::mouseY())
                    )
                );
            }
            ,assets.sprites["icon_ray"])
    );
    menu.push_back(
        MenuEntry(
            [](std::vector<Ray2> &lines){lines.push_back(
                    Ray2(
                        Vector2(0.0f, 0.0f),
                        Vector2(BruxAPI::mouseX(), BruxAPI::mouseY())
                    )
                );
            }
            ,assets.sprites["icon_line"])
    );
    menu.push_back(
        MenuEntry(
            [](std::vector<Ray2> &lines){lines.push_back(
                    Ray2(
                        Vector2(0.0f, 0.0f),
                        Vector2(BruxAPI::mouseX(), BruxAPI::mouseY())
                    )
                );
            }
            ,assets.sprites["icon_circle"])
    );
}

void
Editor::Input(){
    //std::cout << object << std::endl;
    //if(BruxAPI::mousePress(0)){HandleMousePress(BruxAPI::mouseX(), BruxAPI::mouseY());}
    
    line_tool.Input(lines); //line tool
    if(BruxAPI::mouseWheelY() < 0){
        object++;
        object = object%3;
    }
    if(BruxAPI::mouseWheelY() > 0){
        object--;
        if(object < 0) object = 2;
    }
}

void
Editor::HandleMousePress(int _x, int _y){
    for(int o = 0; o < 3; o++){
        if(o == object) menu[o].Spawn(lines);
    }
}

void Editor::Draw(){
    for(int o = 0; o < 3; o++){
        menu[o].Draw(object ,o);
    }
    line_tool.Draw(); //line tool
}