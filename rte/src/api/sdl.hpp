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
