/*=============*\
| SHAPES SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "maths.h"
#include "shapes.h"

///////////
// POINT //
//////////}

//Constructors
xyPnt::xyPnt(){
	x = 0;
	y = 0;
};

xyPnt::xyPnt(float _x, float _y){
	x = _x;
	y = _y;
};

xyPnt::xyPnt(const xyPnt& v){
	x = v.x;
	y = v.y;
};

//Assignment Operators
xyPnt& xyPnt::operator = (const xyPnt& v){
	x = v.x;
	y = v.y;

	return *this;
};

xyPnt& xyPnt::operator += (const xyPnt& v){
	x += v.x;
	y += v.y;

	return *this;
};

xyPnt& xyPnt::operator -= (const xyPnt& v){
	x -= v.x;
	y -= v.y;

	return *this;
};

xyPnt& xyPnt::operator *= (const float s){
	x *= s;
	y *= s;

	return *this;
};

xyPnt& xyPnt::operator /= (const float s){
	x /= s;
	y /= s;

	return *this;
};

//Comparison Operators
bool xyPnt::operator == (const xyPnt& v){
	return(x == v.x && y == v.y);
};

bool xyPnt::operator != (const xyPnt& v){
	return(x != v.x || y != v.y);
};

//Binary operators
const xyPnt xyPnt::operator + (const xyPnt& v){
	xyPnt result(*this);
	result += v;
	return result;
};

const xyPnt xyPnt::operator - (const xyPnt& v){
	xyPnt result(*this);
	result -= v;
	return result;
};

const xyPnt xyPnt::operator * ( const float& s ){
	xyPnt result( *this );
	result *= s;
	return result;
};

const xyPnt xyPnt::operator / ( const float& s ){
	xyPnt result( *this );
	result /= s;
	return result;
};

//Access operator
const float xyPnt::operator[](const int& i){
	switch(i){
		case 0: return x;
		case 1: return y;
		default: return -1;
	};
};

//Functions
float xyPnt::getLength(){
	return(sqrt((x * x) + (y * y)));
};

void xyPnt::setLength(float l){
	float h = getLength();
	float a = (l / h) * x;
	float b = (l / h) * y;

	if(x < 0) a = a * -1;
	if(y < 0) b = b * -1;

	x = a;
	y = b;
};

void xyPnt::rotate(float angle){
	float theta = angle * (pi / 180);
	float nx = (x * cos(theta)) - (y * sin(theta));
	float ny = (x * sin(theta)) + (y * cos(theta));
	x = nx;
	y = ny;
};

void xyPnt::rotate(float angle, float pivx, float pivy){
	//Offset the vector
	x -= pivx;
	y -= pivy;

	//Rotate the vector
	rotate(angle);

	//Reset the vector
	x += pivx;
	y += pivy;
};

float xyPnt::getArea(){
	return 0;
};

//}

////////////
// CIRCLE //
///////////{

xyCir::xyCir(float _x, float _y, float _r){
	x = _x;
	y = _y;
	r = _r;
	type = _CIR;
};

void xyCir::update(float _x, float _y, float _r){
    x = _x;
    y = _y;
    r = _r;
};

//}

//////////
// LINE //
/////////}

xyLin::xyLin(float _x0, float _y0, float _x1, float _y1){
	//Make points
	xyPnt* _p = new xyPnt(_x0, _y0);
	p.push_back(_p);
	_p = new xyPnt(_x1, _y1);
	p.push_back(_p);

	//Assign core members from points
	x = (p[0]->x + p[1]->x) / 2;
	y = (p[0]->y + p[1]->y) / 2;
	l = xyDistance(p[0]->x, p[0]->y, p[1]->x, p[1]->y);
	a = xyPointAngle(p[0]->x, p[0]->y, p[1]->x, p[1]->y);

	//Set type
    type = _LIN;
};

//}
