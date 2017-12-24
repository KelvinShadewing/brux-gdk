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

class Shape{
public:
	float x, y, w, h, a;
	float px[16], py[16];
	const static int type = _SHP;

	Shape(float _x, float _y, float _w, float _h, float _a){
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		a = _a;
	};
};

//////////
// LINE //
//////////

////////////
// CIRCLE //
////////////

class Circle : public Shape{
public:
	const static int type = _CIR;

	Circle(float _x, float _y, float _w){
		x = _x;
		y = _y;
		w = _w;
		h = 0;
		a = 0;
	};
};

bool xyHitTest(Circle *a, Circle *b);

///////////////
// RECTANGLE //
///////////////

#endif
