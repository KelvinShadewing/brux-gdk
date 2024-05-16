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
| SHAPES HEADER |
\*=============*/

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <vector>

namespace ssq {
	class VM;
}

const int _SHP = 0; //Formless shape
const int _LIN = 1; //Line
const int _CIR = 2; //Circle
const int _REC = 3; //Rectangle
const int _TRI = 4; //Triangle
const int _DIA = 5; //Diamond
const int _OVL = 6; //Oval
const int _PLY = 7; //N-polygon
const int _PRM = 8; //Primitive
const int _BDY = 9; //Body (compound shape)

/**
All shapes use a similar system during runtime.
When their positions need to be changed, they
call an update function that moves and rotates
them as needed while also reassigning vertex
positions.

It will probably be easier to update them using
separate position and rotation functions.
*/

class xyPnt
{//Used to store coordinates of each
public:
	float x, y;
	//Constructors
	xyPnt();
	xyPnt(float _x, float _y);
	xyPnt(const xyPnt& v);

	//Assignment 0perators
	xyPnt& operator = (const xyPnt& v);
	xyPnt& operator += (const xyPnt& v);
	xyPnt& operator -= (const xyPnt& v);
	xyPnt& operator *= (const float s);
	xyPnt& operator /= (const float s);

	//Comparison Operators
	bool operator == (const xyPnt& v);
	bool operator != (const xyPnt& v);

    //Binary Operators
	const xyPnt operator + (const xyPnt& v);
	const xyPnt operator - (const xyPnt& v);
	const xyPnt operator * ( const float& s );
	const xyPnt operator / ( const float& s );

	//Access operator
	const float operator[](const int& i);

	//Functions
	float getLength();
	void setLength(float l);
	void rotate(float angle);
	void rotate(float angle, float pivx, float pivy);
	float getArea();
	float dot(xyPnt* p);
};

class xyShape
{
public:
	int type;
	float x, y, a, xmin, xmax, ymin, ymax;
	/**
	Angle is reused as the radius for circles. It will remain
	unchanged when the position is modified. Min and max points
	are updated when the shape changes position so that they do
	not have to be recalculated every time a hit test is run.
	*/

	xyShape(float _x, float _y, float _a, int _type);

	std::vector<xyPnt*> pnt, pbase;
	/**
	pbase is used to store the positions of the vertices as they
	are first created, basically a copy of the shape were it kept
	at point (0,0). pnt is the current position of the points,
	used for detecting collisions.
	*/
	void setpos(float _x, float _y, float _a); //Set position based on absolute coordinates
	void modpos(float _X, float _y, float _a); //Set position based on relative coordinates
	void addpnt(float _x, float _y);
};

bool xyLineLine(xyPnt* a, xyPnt* b, xyPnt* c, xyPnt* d);
bool xyLineLineAPI(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
bool xyPointLine(xyPnt* a, xyPnt* b, xyPnt* c);
bool xyLineCircle(xyPnt* a, xyPnt* b, xyPnt* c, float r);
bool xyLineCircleAPI(float x0, float y0, float x1, float y1, float x2, float y2, float r);
bool xyLinePoint(float lx0, float ly0, float lx1, float ly1, float px, float py);
bool xyHitTest(xyShape* a, xyShape* b);

void xyRegisterShapesAPI(ssq::VM& vm);

#endif
