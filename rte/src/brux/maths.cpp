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
| MATHS SOURCE |
\*============*/

#include "brux/maths.hpp"

#include <simplesquirrel/vm.hpp>

#include "brux/main.hpp"
#include "brux/global.hpp"
#include <time.h>

float xyDistance(float x1, float y1, float x2, float y2) {
	//2D distance formula
	float xd = (float)(x1 - x2);
	float yd = (float)(y1 - y2);

	return sqrt((xd * xd) + (yd * yd));
}

float xyDistance3(float x1, float y1, float z1, float x2, float y2, float z2) {
	float xd = (float)(x1 - x2);
	float yd = (float)(y1 - y2);
	float zd = (float)(z1 - z2);

	return sqrt((xd * xd) + (yd * yd) + (zd * zd));
}

bool xyInDistance2(float x1, float y1, float x2, float y2, float distance) {
	//Faster than xyDistance for checking within range
	//xyDistance is better for when the actual distance needs to be shown
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= distance * distance;
}

int xyRandomInt(int mx) {
	int numb = rand();
	numb %= mx;

	return numb;
}

float xyRandomFloat(float mx) {
	return (static_cast<float>(rand()) / (float)RAND_MAX) * mx;
}

float xyWrap(float x, float a0, float a1) {
	float mx = std::max(a0, a1);
	float mn = std::min(a0, a1);

	float diff = mx - mn + 1;

	if(x >= 0) return mn + fmodf(x, diff);
	if(x < 0) return mx + fmod(x, diff);
	return 0; //Just so GCC is happy
}

int xyFloor(float f) {
	return static_cast<int>(std::floor(f));
}

int xyCeil(float f) {
	return static_cast<int>(std::ceil(f));
}

int xyRound(float f) {
	return static_cast<int>(std::round(f));
}

float xyPointAngle(float x1, float y1, float x2, float y2) {
	return atan2(y2 - y1, x2 - x1) * (180 / pi);
}

bool xyPointInBox(float x1, float y1, float x2, float y2, float px, float py) {
	//Get min/max of box in case box is flipped
	float t, b, l, r;
	l = std::min(x1, x2);
	r = std::max(x1, x2);
	t = std::min(y1, y2);
	b = std::max(y1, y2);

	return px < r && px > l && py < b && py > t;
}

float xyLenDirX(float l, float d) {
	return l * cos(d * pi / 180);
}

float xyLenDirY(float l, float d) {
	return l * sin(d * pi / 180);
}

std::string xyBinstr(int i) {
	int l = static_cast<int>(log2(i)) + 1;
	std::string s;

	switch (l) {
		case 0:
			s = "0";
			break;
		case 1:
			s = std::bitset<1>(i).to_string();
			break;
		case 2:
			s = std::bitset<2>(i).to_string();
			break;
		case 3:
			s = std::bitset<3>(i).to_string();
			break;
		case 4:
			s = std::bitset<4>(i).to_string();
			break;
		case 5:
			s = std::bitset<5>(i).to_string();
			break;
		case 6:
			s = std::bitset<6>(i).to_string();
			break;
		case 7:
			s = std::bitset<7>(i).to_string();
			break;
		case 8:
			s = std::bitset<8>(i).to_string();
			break;
		case 9:
			s = std::bitset<9>(i).to_string();
			break;
		case 10:
			s = std::bitset<10>(i).to_string();
			break;
		case 11:
			s = std::bitset<11>(i).to_string();
			break;
		case 12:
			s = std::bitset<12>(i).to_string();
			break;
		case 13:
			s = std::bitset<13>(i).to_string();
			break;
		case 14:
			s = std::bitset<14>(i).to_string();
			break;
		case 15:
			s = std::bitset<15>(i).to_string();
			break;
		case 16:
			s = std::bitset<16>(i).to_string();
			break;
		case 17:
			s = std::bitset<17>(i).to_string();
			break;
		case 18:
			s = std::bitset<18>(i).to_string();
			break;
		case 19:
			s = std::bitset<19>(i).to_string();
			break;
		case 20:
			s = std::bitset<20>(i).to_string();
			break;
		case 21:
			s = std::bitset<21>(i).to_string();
			break;
		case 22:
			s = std::bitset<22>(i).to_string();
			break;
		case 23:
			s = std::bitset<23>(i).to_string();
			break;
		case 24:
			s = std::bitset<24>(i).to_string();
			break;
		case 25:
			s = std::bitset<25>(i).to_string();
			break;
		case 26:
			s = std::bitset<26>(i).to_string();
			break;
		case 27:
			s = std::bitset<27>(i).to_string();
			break;
		case 28:
			s = std::bitset<28>(i).to_string();
			break;
		case 29:
			s = std::bitset<29>(i).to_string();
			break;
		case 30:
			s = std::bitset<30>(i).to_string();
			break;
		case 31:
			s = std::bitset<31>(i).to_string();
			break;
		case 32:
			s = std::bitset<32>(i).to_string();
			break;
		default:
			s = std::bitset<64>(i).to_string();
			break;
	}

	return s;
}

void xyRandomSeed(int seed = -1) {
	if(seed != -1)
		srand(time(NULL));
	else
		srand(seed);
}

float xyClamp(float val, float min, float max) {
	if(min > max) {
		if(val > min)
			return min;
		if(val < max)
			return max;
	}

	if(val < min)
		return min;
	if(val > max)
		return max;

	return val;
}

float xyLerp(float a, float b, float t) {
	return a + (b - a) * t;
}

void xyRegisterMathsAPI(ssq::VM& vm) {
	vm.addFunc("randFloat", xyRandomFloat); // Doc'd
	vm.addFunc("randInt", xyRandomInt); // Doc'd
	vm.addFunc("distance2", xyDistance); // Doc'd
	vm.addFunc("inDistance2", xyInDistance2);
	vm.addFunc("distance3", xyDistance3);
	vm.addFunc("wrap", xyWrap); // Doc'd
	vm.addFunc("floor", xyFloor); // Doc'd
	vm.addFunc("ceil", xyCeil); // Doc'd
	vm.addFunc("round", xyRound); // Doc'd
	vm.addFunc("pointAngle", xyPointAngle); // Doc'd
	vm.addFunc("abs", static_cast<float(*)(float)>(std::abs)); // Doc'd
	vm.addFunc("lendirX", xyLenDirX); // Doc'd
	vm.addFunc("lendirY", xyLenDirY); // Doc'd
	vm.addFunc("binstr", xyBinstr); // Doc'd
	vm.addFunc("randSeed", xyRandomSeed, ssq::DefaultArguments<int>(-1));
	vm.addFunc("clamp", xyClamp);
	vm.addFunc("lerp", xyLerp);
}
