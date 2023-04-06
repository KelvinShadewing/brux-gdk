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

#include "api/shapes.hpp"

#include "brux/main.hpp"

#include "brux/shapes.hpp"

namespace BruxAPI {

////////////
// SHAPES //
////////////

bool hitLineLine(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);
	xyPnt d(x3, y3);

	return xyLineLine(&a, &b, &c, &d);
}

bool hitLineCircle(float x0, float y0, float x1, float y1, float x2, float y2, float r) {
	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);

	return xyLineCircle(&a, &b, &c, r);
}

bool hitLinePoint(float x0, float y0, float x1, float y1, float x2, float y2) {
	return xyLinePoint(x0, y0, x1, y1, x2, y2);
}

} // namespace BruxAPI
