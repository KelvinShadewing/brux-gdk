#ifndef LINE_TOOL_H
#define LINE_TOOL_H

#include "../../math2/ray2.hpp"
#include <vector>

class LineTool{
public:
    std::vector<Vector2> points;

    void Input(std::vector<Ray2> &_rays);
    void Draw();

};



#endif