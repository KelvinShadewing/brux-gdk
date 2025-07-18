//  Brux - Flat Layer Oriented Perspective
//  Copyright (C) 2025 KelvinShadewing
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

/*===========*\
| FLOP HEADER |
\*===========*/

#ifndef _BRUX_FLOP_HPP_
#define _BRUX_FLOP_HPP_

void xyFlopDraw(int src, int x, int y, int w, int h, int cx, int cy, int ca, int near, int far, int fov, int scale);
void xyRegisterFlopAPI(ssq::VM& vm);

#endif
