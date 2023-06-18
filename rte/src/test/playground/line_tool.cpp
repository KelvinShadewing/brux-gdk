#include "line_tool.hpp"
#include "../../api/input.hpp"
#include "../../api/sdl.hpp"
void
LineTool::Input(std::vector<Ray2> &_rays){

    if(BruxAPI::mousePress(0)) points.push_back(Vector2(BruxAPI::mouseX(), BruxAPI::mouseY()));
    
    if(points.size() == 2){
        points.clear();
        _rays.push_back(
            Ray2(points[0],points[1])
        );
    }

}

void
LineTool::Draw(){

    if(points.size() == 1){
        BruxAPI::drawLine(points[0].x, points[0].y, BruxAPI::mouseX(), BruxAPI::mouseY());
    }

}