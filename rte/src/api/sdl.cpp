//  Brux - SDL API
//  Copyright (C) 2016 KelvinShadewing
//                2023 Vankata453
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
