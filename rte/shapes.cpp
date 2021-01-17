/*=============*\
| SHAPES SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "maths.h"
#include "shapes.h"

/*
This part is being put on hold.
It's being implemented in Squirrel for now.
*/

///////////
// POINT //
//////////{

//Constructors
xyPnt::xyPnt()
{
	x = 0;
	y = 0;
};

xyPnt::xyPnt(float _x, float _y)
{
	x = _x;
	y = _y;
};

xyPnt::xyPnt(const xyPnt& v)
{
	x = v.x;
	y = v.y;
};

//Assignment Operators
xyPnt& xyPnt::operator = (const xyPnt& v)
{
	x = v.x;
	y = v.y;

	return *this;
};

xyPnt& xyPnt::operator += (const xyPnt& v)
{
	x += v.x;
	y += v.y;

	return *this;
};

xyPnt& xyPnt::operator -= (const xyPnt& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
};

xyPnt& xyPnt::operator *= (const float s)
{
	x *= s;
	y *= s;

	return *this;
};

xyPnt& xyPnt::operator /= (const float s)
{
	x /= s;
	y /= s;

	return *this;
};

//Comparison Operators
bool xyPnt::operator == (const xyPnt& v)
{
	return(x == v.x && y == v.y);
};

bool xyPnt::operator != (const xyPnt& v)
{
	return(x != v.x || y != v.y);
};

//Binary operators
const xyPnt xyPnt::operator + (const xyPnt& v)
{
	xyPnt result(*this);
	result += v;
	return result;
};

const xyPnt xyPnt::operator - (const xyPnt& v)
{
	xyPnt result(*this);
	result -= v;
	return result;
};

const xyPnt xyPnt::operator * ( const float& s )
{
	xyPnt result( *this );
	result *= s;
	return result;
};

const xyPnt xyPnt::operator / ( const float& s )
{
	xyPnt result( *this );
	result /= s;
	return result;
};

//Access operator
const float xyPnt::operator[](const int& i)
{
	switch(i){
		case 0: return x;
		case 1: return y;
		default: return -1;
	};
};

//Functions
float xyPnt::getLength()
{
	return(sqrt((x * x) + (y * y)));
};

void xyPnt::setLength(float l)
{
	float h = getLength();
	float a = (l / h) * x;
	float b = (l / h) * y;

	if(x < 0) a = a * -1;
	if(y < 0) b = b * -1;

	x = a;
	y = b;
};

void xyPnt::rotate(float angle)
{
	float theta = angle * (pi / 180);
	float nx = (x * cos(theta)) - (y * sin(theta));
	float ny = (x * sin(theta)) + (y * cos(theta));
	x = nx;
	y = ny;
};

void xyPnt::rotate(float angle, float pivx, float pivy)
{
	//Offset the vector
	x -= pivx;
	y -= pivy;

	//Rotate the vector
	rotate(angle);

	//Reset the vector
	x += pivx;
	y += pivy;
};

float xyPnt::getArea()
{
	return 0;
};

//}

///////////
// SHAPE //
//////////{

bool xyLineLine(xyPnt* a, xyPnt* b, xyPnt* c, xyPnt* d)
{
	float denom = ((b->x - a->x) * (d->y - c->y)) - ((b->y - a->y) * (d->x - c->x));
	float nume0 = ((a->y - c->y) * (d->x - c->x)) - ((a->x - c->x) * (d->y - c->y));
	float nume1 = ((a->y - c->y) * (b->x - a->x)) - ((a->x - c->x) * (b->y - a->y));

	if(denom == 0) return nume0 == 0 && nume1 == 0;

	float r = nume0 / denom;
	float s = nume1 / denom;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
};

bool xyPointLine(xyPnt* a, xyPnt* b, xyPnt* c)
{
};

bool xyHitTest(xyShape* a, xyShape* b)
{
	//Get type of A
	switch(a->type)
	{
		case _LIN:
			switch(b->type)
			{
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
			switch(b->type)
			{
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
			switch(b->type)
			{
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
			switch(b->type)
			{
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
			switch(b->type)
			{
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
			switch(b->type)
			{
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
			switch(b->type)
			{
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
			switch(b->type)
			{
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
};

//}
