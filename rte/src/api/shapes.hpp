//  Brux - Shapes API
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
