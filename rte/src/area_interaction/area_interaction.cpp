#include "../math/rectangle2.hpp"
#include <vector>

void::AreaOverlap(Rectangle2 a, std::vector<Rectangle2> *_layer){
    for(auto b : *_layer){
        if (b.id == a.id) continue;
        if (!(
            (a.position.x > (b.position.x + b.size.x)) || // is the left side greater than the other rect's right side?
            ((a.position.x + a.size.x) < b.position.x) ||       // is the right side less than the other rect's left side?
            (a.position.y > (b.position.y + b.size.y)) || // is the lower side greater than the other rect's upper side?
            ((a.position.y + a.position.y) < b.position.y)))         // is the upper side less than the other rect's lower side?
        {
            return;
        }
        return;
    }
}