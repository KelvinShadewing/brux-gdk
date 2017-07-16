/*==========*\
| DOT SOURCE |
\*==========*/

#include "shapes.h"
#include "main.h"
#include "global.h"
#include "maths.h"

//Constructors
xyVect::xyVect(){
	m_className = "dot";
	x = 0;
	y = 0;
};

xyVect::xyVect(float _x, float _y){
	m_className = "dot";
	x = _x;
	y = _y;
};

xyVect::xyVect(const xyVect& v){
	m_className = "dot";
	x = v.x;
	y = v.y;
};



//Assignment Operators
xyVect& xyVect::operator = (const xyVect& v){
	x = v.x;
	y = v.y;

	return *this;
};

xyVect& xyVect::operator += (const xyVect& v){
	x += v.x;
	y += v.y;

	return *this;
};

xyVect& xyVect::operator -= (const xyVect& v){
	x -= v.x;
	y -= v.y;

	return *this;
};

xyVect& xyVect::operator *= (const float s){
	x *= s;
	y *= s;

	return *this;
};

xyVect& xyVect::operator /= (const float s){
	if(s != 0){
		x /= s;
		y /= s;
	} else throw("Divide by zero.");

	return *this;
};



//Comparison Operators
bool xyVect::operator == (const xyVect& v){
	return(x == v.x && y == v.y);
};

bool xyVect::operator != (const xyVect& v){
	return(x != v.x || y != v.y);
};



//Binary Operators
const xyVect xyVect::operator + (const xyVect& v){
	xyVect result(*this);
	result += v;
	return result;
};

const xyVect xyVect::operator - (const xyVect& v){
	xyVect result(*this);
	result -= v;
	return result;
};

const xyVect xyVect::operator * (const float s){
	xyVect result(*this);
	result *= s;
	return result;
};

const xyVect xyVect::operator / (const float s){
	xyVect result(*this);
	result /= s;
	return result;
};



//Accessor Operator
float xyVect::operator[](const int& i){
	switch(i){
		case 0: return x;
		case 1: return y;
		default: return -1;
	};
};



//Functions
float xyVect::getLength(){
	return x * y;
};

void xyVect::setLength(float l){
	float h = getLength();
	float a = (l / h) * x;
	float b = (l / h) * y;

	if(x < 0) a = a * -1;
	if(y < 0) b = b * -1;

	x = a;
	y = b;
};

void xyVect::rotate(float angle){
	float theta = angle * (pi / 180);
	float nx = (x * cos(theta)) - (y * sin(theta));
	float ny = (x * sin(theta)) + (y * cos(theta));
	x = nx;
	y = ny;
};

void xyVect::rotate(float angle, float pivx, float pivy){
	//Offset the vector
	x -= pivx;
	y -= pivy;

	//Rotate the vector
	rotate(angle);

	//Reset the vector
	x += pivx;
	y += pivy;
};

float xyVect::getArea(){
	return 0;
};