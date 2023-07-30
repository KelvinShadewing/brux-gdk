//  Brux - Maths API
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

#ifndef BRUX_API_MATHS_HEADER
#define BRUX_API_MATHS_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

///////////
// MATHS //
///////////

float randFloat(float a); // Doc'd
int randInt(int a); // Doc'd
float distance2(float x1, float y1, float x2, float y2); // Doc'd
bool inDistance2(float x1, float y1, float x2, float y2, float d);
float distance3(float x1, float y1, float z1, float x2, float y2, float z2);
float wrap(float x, float mx, float mn); // Doc'd
int floor(float f); // Doc'd
int ceil(float f); // Doc'd
int round(float f); // Doc'd
float pointAngle(float x1, float y1, float x2, float y2); // Doc'd
float abs(float f); // Doc'd
float lendirX(float l, float d); // Doc'd
float lendirY(float l, float d); // Doc'd
std::string binstr(int i); // Doc'd

} // namespace BruxAPI

#endif
