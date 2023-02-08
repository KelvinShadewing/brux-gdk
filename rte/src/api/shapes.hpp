#ifndef BRUX_API_SHAPES_HEADER
#define BRUX_API_SHAPES_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Shapes
bool hitLineLine(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3); // Doc'd
bool hitLineCircle(float x0, float y0, float x1, float y1, float x2, float y2, float r); // Doc'd
bool hitLinePoint(float x0, float y0, float x1, float y1, float x2, float y2); // Doc'd

} // namespace BruxAPI

#endif
