#ifndef BRUX_API_SDL_HEADER
#define BRUX_API_SDL_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// SDL_gfx
void drawCircle(float x, float y, float r, bool f); // Doc'd
void drawRec(float x, float y, float w, float h, bool f); // Clone of `drawRect()`
void drawRect(float x, float y, float w, float h, bool f); // Doc'd
void drawPoint(float x, float y); // Doc'd
void drawLine(float x1, float y1, float x2, float y2); // Doc'd
void drawLineWide(float x1, float y1, float x2, float y2, float w); // Doc'd

} // namespace BruxAPI

#endif
