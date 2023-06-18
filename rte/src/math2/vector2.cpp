#include <cmath>
#include "vector2.hpp"

Vector2 Vector2::Normalize(){
    float n_x = x/ std::sqrt(x*x + y*y);
    float n_y = y/ std::sqrt(x*x + y*y);
    return Vector2(n_x, n_y);
}

float Vector2::Magnitude(){
    return std::sqrt(x*x + y*y);
}