/*=============*\
| SHAPES HEADER |
\*=============*/

#ifndef _SHAPES_H_
#define _SHAPES_H_

const int _SHP = 0;
const int _LIN = 1;
const int _CIR = 2;
const int _REC = 3;
const int _TRI = 4;
const int _DIA = 5;
const int _OVL = 6;
const int _PLY = 7;
const int _PRM = 8;
const int _BDY = 9;

/*
All shapes use a similar system during runtime.
When their positions need to be changed, they
call an update function that moves and rotates
them as needed while also reassigning vertex
positions.

I'm not sure how to do primitives just yet.
*/

class xyPnt{//Used to store coordinates of each
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
};

class xyShp{
public:
	int type;
	vector<xyPnt*> p;
};

class xyCir : public xyShp{
private:
	float x, y, r;
public:
	xyCir(float _x, float _y, float _r);
	void update(float _x, float _y, float _r);
};

class xyLin : public xyShp{
private:
	float x, y, l, a;
public:
	xyLin(float _x0, float _y0, float _x1, float _y1);
	void update(float _x, float _y, float _l, float _a);
};

#endif
