/*==========*\
| DOT SOURCE |
\*==========*/

#include "shapes.h"
#include "main.h"
#include "global.h"
#include "maths.h"

//Constructors
xyDot::xyDot(){
	m_className = "dot";
	x = 0;
	y = 0;
};

xyDot::xyDot(float _x, float _y){
	m_className = "dot";
	x = _x;
	y = _y;
};

xyDot::xyDot(const xyDot& v){
	m_className = "dot";
	x = v.x;
	y = v.y;
};



//Assignment Operators
xyDot& xyDot::operator = (const xyDot& v){
	x = v.x;
	y = v.y;

	return *this;
};

xyDot& xyDot::operator += (const xyDot& v){
	x += v.x;
	y += v.y;

	return *this;
};

xyDot& xyDot::operator -= (const xyDot& v){
	x -= v.x;
	y -= v.y;

	return *this;
};

xyDot& xyDot::operator *= (const float s){
	x *= s;
	y *= s;

	return *this;
};

xyDot& xyDot::operator /= (const float s){
	if(s != 0){
		x /= s;
		y /= s;
	} else throw("Divide by zero.");

	return *this;
};



//Comparison Operators
bool xyDot::operator == (const xyDot& v){
	return(x == v.x && y == v.y);
};

bool xyDot::operator != (const xyDot& v){
	return(x != v.x || y != v.y);
};



//Binary Operators
const xyDot xyDot::operator + (const xyDot& v){
	xyDot result(*this);
	result += v;
	return result;	
};

const xyDot xyDot::operator - (const xyDot& v){
	xyDot result(*this);
	result -= v;
	return result;	
};

const xyDot xyDot::operator * (const float s){
	xyDot result(*this);
	result *= s;
	return result;	
};

const xyDot xyDot::operator / (const float s){
	xyDot result(*this);
	result /= s;
	return result;	
};



//Accessor Operator
float xyDot::operator[](const int& i){
	switch(i){
		case 0: return x;
		case 1: return y;
		default: return -1;
	};
};



//Functions
float xyDot::getLength(){
	return x * y;
};

void xyDot::setLength(float l){
	float h = getLength();
	float a = (l / h) * x;
	float b = (l / h) * y;

	if(x < 0) a = a * -1;
	if(y < 0) b = b * -1;

	x = a;
	y = b;
};

void xyDot::rotate(float angle){
	float theta = angle * (pi / 180);
	float nx = (x * cos(theta)) - (y * sin(theta));
	float ny = (x * sin(theta)) + (y * cos(theta));
	x = nx;
	y = ny;
};

void xyDot::rotate(float angle, float pivx, float pivy){
	//Offset the vector
	x -= pivx;
	y -= pivy;

	//Rotate the vector
	rotate(angle);

	//Reset the vector
	x += pivx;
	y += pivy;
};

float xyDot::getArea(){
	return 0;
};

//Hit Tests
bool xyDot::hitTest(xyDot* other){
	return(x == other->x && y == other->y);
};

bool xyDot::hitTest(xyLin* other){
	return 0;
};

bool xyDot::hitTest(xyCir* other){
	return(xyDistance(x, y, other->x, other->y) <= other->r);
};

bool xyDot::hitTest(xyEgg* other){
	return 0;
};

bool xyDot::hitTest(xyRec* other){
	return 0;
};

bool xyDot::hitTest(xyDia* other){
	return 0;
};

bool xyDot::hitTest(xyTri* other){
	return 0;
};