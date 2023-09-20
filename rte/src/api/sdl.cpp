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

void drawCircle(int x, int y, int radius, bool filled) {
	if (filled) {
		filledCircleColor(gvRender, x, y, radius, gvDrawColor);
		return;
	}
	
	circleColor(gvRender, x, y, radius, gvDrawColor);
}

void drawRec(int x, int y, int w, int h, bool filled) {
	drawRect(x, y, w, h, filled);
}

void drawRect(int x, int y, int w, int h, bool filled) {
	if (filled)
		boxColor(gvRender, x, y, x + w, y + h, gvDrawColor);
	else
		rectangleColor(gvRender, x, y, x + w, y + h, gvDrawColor);
}

void drawPoint(int x, int y) {
	pixelColor(gvRender, x, y, gvDrawColor);
}

void drawLine(int x1, int y1, int x2, int y2) {
	thickLineColor(gvRender, x1, y1, x2, y2, 1, gvDrawColor);
}

void drawLineWide(int x1, int y1, int x2, int y2, int w) {
	thickLineColor(gvRender, x1, y1, x2, y2, w, gvDrawColor);
}

} // namespace BruxAPI
