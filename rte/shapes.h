/*=============*\
| SHAPES HEADER |
\*=============*/

#ifndef _SHAPES_H_
#define _SHAPES_H_

const int shVect = 0;
const int shLine = 1;
const int shCirc = 2;
const int shRect = 3;
const int shKite = 4;
const int shTria = 5;
const int shPoly = 6;
const int shBody = 7;

class xyShape{
public:
	//Variables
	int t, n;
	float x, y, x1, y1, x2, y2, x3, y3, x4, y4, w, h, a, s, r;

	//Functions
	xyShape(int _t, float _x, float _y, float _x1, float _y1, float _x2, float _y2, float _x3, float _y3, float _x4, float _y4, float _w, float _h, float _a, float _s, float _r);
};

//Hit test functions
bool xyHitTest(xyShape* a, xyShape* b);
bool xyHitTestVV(xyShape* a, xyShape* b);
bool xyHitTestCC(xyShape* a, xyShape* b);
bool xyHitTestLL(xyShape* a, xyShape* b);
bool xyHitTestCL(xyShape* a, xyShape* b);

//Shape math functions
bool xyPointInShape(float x, float y, xyShape* a);
float xyGetArea(xyShape* a);

//Other functions
void xyDrawShape(Uint32 shape, float x, float y);

#endif
