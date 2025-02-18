//  Brux - Shapes
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

/*=============*\
| SHAPES SOURCE |
\*=============*/

#include "brux/shapes.hpp"

#include <simplesquirrel/vm.hpp>

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/maths.hpp"

/*\
This part is being put on hold.
It's being implemented in Squirrel for now.
Once all the math is worked out, it will be
moved here to C++. How shapes are addressed
will also be changed to suit the new system.

Some functions will still need to be done in
Squirrel, just to make them easier, but all
the heavy math will be done here for
performance reasons.
\*/

///////////
// POINT //
///////////

//Constructors
xyPnt::xyPnt() {
	x = 0;
	y = 0;
}

xyPnt::xyPnt(float _x, float _y) {
	x = _x;
	y = _y;
}

xyPnt::xyPnt(const xyPnt& v) {
	x = v.x;
	y = v.y;
}

//Assignment Operators
xyPnt& xyPnt::operator = (const xyPnt& v) {
	x = v.x;
	y = v.y;

	return *this;
}

xyPnt& xyPnt::operator += (const xyPnt& v) {
	x += v.x;
	y += v.y;

	return *this;
}

xyPnt& xyPnt::operator -= (const xyPnt& v) {
	x -= v.x;
	y -= v.y;

	return *this;
}

xyPnt& xyPnt::operator *= (const float s) {
	x *= s;
	y *= s;

	return *this;
}

xyPnt& xyPnt::operator /= (const float s) {
	x /= s;
	y /= s;

	return *this;
}

//Comparison Operators
bool xyPnt::operator == (const xyPnt& v) {
	return(x == v.x && y == v.y);
}

bool xyPnt::operator != (const xyPnt& v) {
	return(x != v.x || y != v.y);
}

//Binary operators
const xyPnt xyPnt::operator + (const xyPnt& v) {
	xyPnt result(*this);
	result += v;
	return result;
}

const xyPnt xyPnt::operator - (const xyPnt& v) {
	xyPnt result(*this);
	result -= v;
	return result;
}

const xyPnt xyPnt::operator * ( const float& s ) {
	xyPnt result( *this );
	result *= s;
	return result;
}

const xyPnt xyPnt::operator / ( const float& s ) {
	xyPnt result( *this );
	result /= s;
	return result;
}

//Access operator
const float xyPnt::operator[](const int& i) {
	switch(i) {
		case 0: return x;
		case 1: return y;
		default: return -1;
	}
}

//Functions
float xyPnt::getLength() {
	return(sqrt((x * x) + (y * y)));
}

void xyPnt::setLength(float l) {
	float h = getLength();
	float a = (l / h) * x;
	float b = (l / h) * y;

	if(x < 0) a = a * -1;
	if(y < 0) b = b * -1;

	x = a;
	y = b;
}

void xyPnt::rotate(float angle) {
	float theta = angle * (pi / 180);
	float nx = (x * cos(theta)) - (y * sin(theta));
	float ny = (x * sin(theta)) + (y * cos(theta));
	x = nx;
	y = ny;
}

void xyPnt::rotate(float angle, float pivx, float pivy) {
	//Offset the vector
	x -= pivx;
	y -= pivy;

	//Rotate the vector
	rotate(angle);

	//Reset the vector
	x += pivx;
	y += pivy;
}

float xyPnt::getArea() {
	return 0;
}

float xyPnt::dot(xyPnt* p) {
	return (x * p->x) + (y * p->y);
}



///////////
// SHAPE //
///////////

xyShape::xyShape(float _x, float _y, float _a, int _type) {
	x = _x;
	y = _y;
	a = _a;
	type = _type;
};



bool xyLineLine(xyPnt* a, xyPnt* b, xyPnt* c, xyPnt* d) {
	float denom = ((b->x - a->x) * (d->y - c->y)) - ((b->y - a->y) * (d->x - c->x));
	float nume0 = ((a->y - c->y) * (d->x - c->x)) - ((a->x - c->x) * (d->y - c->y));
	float nume1 = ((a->y - c->y) * (b->x - a->x)) - ((a->x - c->x) * (b->y - a->y));

	if(denom == 0) return nume0 == 0 && nume1 == 0;

	float r = nume0 / denom;
	float s = nume1 / denom;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool xyLineLineAPI(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);
	xyPnt d(x3, y3);

	return xyLineLine(&a, &b, &c, &d);
}

bool xyPointLine(xyPnt* a, xyPnt* b, xyPnt* c) {
	return false; //TODO: Fill this in
}

bool xyLineCircle(xyPnt* a, xyPnt* b, xyPnt* c, float r) {
	if(xyDistance(a->x, a->y, c->x, c->y) <= r) return true;
	if(xyDistance(b->x, b->y, c->x, c->y) <= r) return true;

	float distX = a->x - b->x;
	float distY = a->y - b->y;
	float len = sqrt((distX * distX) + (distY * distY));

	float dot = ( ((c->x - a->x) * (b->x - a->x)) + ((c->y - a->y) * (b->y - a->y)) ) / static_cast<float>(pow(len, 2));
	float cx = a->x + (dot * (b->x - a->x));
	float cy = a->y + (dot * (b->y - a->y));

	if (!xyLinePoint(a->x, a->y, b->x, b->y, cx, cy)) return false;

	distX = cx - c->x;
	distY = cy - c->y;
	len = sqrt((distX * distX) + (distY * distY));

	return (len <= r);
}

bool xyLineCircleAPI(float x0, float y0, float x1, float y1, float x2, float y2, float r) {
	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);

	return xyLineCircle(&a, &b, &c, r);
}

bool xyLinePoint(float lx0, float ly0, float lx1, float ly1, float px, float py) {
	float ll = xyDistance(lx0, ly0, lx1, ly1);
	float d1 = xyDistance(lx0, ly0, px, py);
	float d2 = xyDistance(px, py, lx1, ly1);

	return (d1 + d2 <= ll + 1 && d1 + d2 >= ll - 1); //Literal is floating point buffer
}

bool xyHitTest(xyShape* a, xyShape* b) {
	//Get type of A
	switch(a->type) {
		case _LIN:
			switch(b->type) {
				case _LIN:
					return xyLineLine(a->pnt[0], a->pnt[1], b->pnt[0], b->pnt[1]);
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _CIR:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return (xyDistance(a->x, a->y, b->x, b->y) <= a->a + b->a);
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _REC:
			switch(b->type){
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _TRI:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _DIA:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _OVL:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _PLY:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _PRM:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		case _BDY:
			switch(b->type) {
				case _LIN:
					return 0;
					break;
				case _CIR:
					return 0;
					break;
				case _REC:
					return 0;
					break;
				case _TRI:
					return 0;
					break;
				case _DIA:
					return 0;
					break;
				case _OVL:
					return 0;
					break;
				case _PLY:
					return 0;
					break;
				case _PRM:
					return 0;
					break;
				case _BDY:
					return 0;
					break;
				default:
					return 0;
					break;
			};
			break;
		default:
			return 0;
			break;
	};
}


void xyRegisterShapesAPI(ssq::VM& vm) {
	vm.addFunc("hitLineLine", xyLineLineAPI); // Doc'd
	vm.addFunc("hitLineCircle", xyLineCircleAPI); // Doc'd
	vm.addFunc("hitLinePoint", xyLinePoint); // Doc'd
}
