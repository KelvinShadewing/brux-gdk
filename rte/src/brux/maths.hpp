//  Brux - Maths
//  Copyright (C) 2016 KelvinShadewing
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

/*============*\
| MATHS HEADER |
\*============*/

#ifndef _XYMATHS_H_
#define _XYMATHS_H_

#include <string>

namespace ssq {
	class VM;
}

float xyDistance(float x1, float y1, float x2, float y2);	//Distance between two points
float xyDistance3(float x1, float y1, float z1, float x2, float y2, float z2);
bool xyInDistance2(float x1, float y1, float x2, float y2, float distance);
int xyRandomInt(int mx);	//Generate a random integer
float xyRandomFloat(float mx);	//Generate a random float
float xyWrap(float x,float a0,float a1); //Wrap an integer
int xyFloor(float f);
int xyCeil(float f);
int xyRound(float f);
float xyPointAngle(float x1, float y1, float x2, float y2); //Get the angle between two points
bool xyPointInBox(float x1, float y1, float x2, float y2, float px, float py);
float xyLenDirX(float l, float d);
float xyLenDirY(float l, float d);
std::string xyBinstr(int i);
float xyClamp(float val, float min, float max);
float xyLerp(float a, float b, float t);

void xyRegisterMathsAPI(ssq::VM& vm);

#endif
