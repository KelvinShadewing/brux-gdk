/*===========*\
|SHAPES HEADER|
\*===========*/

#ifndef _SHAPES_H_
#define _SHAPES_H_

//Prototypes
class xyShape;
class xyDot;
class xyLin;
class xyCir;
class xyEgg;
class xyRec;
class xyDia;
class xyTri;

//Shape base class
class xyShape{
protected:
	char *m_className;
	int m_number;
public:
	char *getName();
};

//Vector
class xyDot : public xyShape{
public:
	//Variables
	float x, y;

	//Constructors
	xyDot();
	xyDot(float _x, float _y);
	xyDot(const xyDot& v);

	//Assignment 0perators
	xyDot& operator = (const xyDot& v);
	xyDot& operator += (const xyDot& v);
	xyDot& operator -= (const xyDot& v);
	xyDot& operator *= (const float s);
	xyDot& operator /= (const float s);

	//Comparison Operators
	bool operator == (const xyDot& v);
	bool operator != (const xyDot& v);

	//Binary Operators
	const xyDot operator + (const xyDot& v);
	const xyDot operator - (const xyDot& v);
	const xyDot operator * (const float s);
	const xyDot operator / (const float s);

	//Access Operator
	float operator[](const int& i);

	//Functions
	float getLength();
	void setLength(float l);
	void rotate(float angle);
	void rotate(float angle, float pivx, float pivy);
	float getArea();

	//Hit Tests
	bool hitTest(xyDot* other);
	bool hitTest(xyLin* other);
	bool hitTest(xyCir* other);
	bool hitTest(xyEgg* other);
	bool hitTest(xyRec* other);
	bool hitTest(xyDia* other);
	bool hitTest(xyTri* other);
};

//Line
class xyLin : public xyShape{
private:
	xyDot *point[2];

public:
	float x1, y1, x2, y2;

	//Constructor
	xyLin();
	xyLin(float _x1, float _y1, float _x2, float _y2);

	//Hit test
	bool hitTest(xyDot* other);
	bool hitTest(xyLin* other);
	bool hitTest(xyCir* other);
	bool hitTest(xyEgg* other);
	bool hitTest(xyRec* other);
	bool hitTest(xyDia* other);
	bool hitTest(xyTri* other);

	//Hit test
	void update();
};

class xyCir : public xyShape{
public:
	//Variables
	float x, y, r;

	//Constructor
	xyCir();
	xyCir(float _x, float _y, float _r);

	//Hit test
	bool hitTest(xyDot* other);
	bool hitTest(xyLin* other);
	bool hitTest(xyCir* other);
	bool hitTest(xyEgg* other);
	bool hitTest(xyRec* other);
	bool hitTest(xyDia* other);
	bool hitTest(xyTri* other);
};

#endif
