#include "api/sdl.hpp"

#include "brux/global.hpp"
#include "brux/graphics.hpp"

namespace BruxAPI {

/////////////
// SDL_GFX //
/////////////

void drawCircle(float x, float y, float r, bool f) {
	if (f)
		filledCircleColor(gvRender, x, y, r, gvDrawColor);
	else
		circleColor(gvRender, x, y, r, gvDrawColor);
}

void drawRec(float x, float y, float w, float h, bool f) {
	drawRect(x, y, w, h, f);
}

void drawRect(float x, float y, float w, float h, bool f) {
	if (f)
		boxColor(gvRender, x, y, x + w, y + h, gvDrawColor);
	else
		rectangleColor(gvRender, x, y, x + w, y + h, gvDrawColor);
}

void drawPoint(float x, float y) {
	pixelColor(gvRender, x, y, gvDrawColor);
}

void drawLine(float x1, float y1, float x2, float y2) {
	thickLineColor(gvRender, x1, y1, x2, y2, 1, gvDrawColor);
}

void drawLineWide(float x1, float y1, float x2, float y2, float w) {
	thickLineColor(gvRender, x1, y1, x2, y2, w, gvDrawColor);
}

} // namespace BruxAPI
