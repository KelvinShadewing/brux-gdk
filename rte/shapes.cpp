/*=============*\
| SHAPES SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "maths.h"
#include "shapes.h"

xyShape::xyShape(int _t, float _x, float _y, float _x1, float _y1, float _x2, float _y2, float _x3, float _y3, float _x4, float _y4, float _w, float _h, float _a, float _s, float _r){
	//Assign self to gobal array
	if(vcShapes.size() == 0){
		vcShapes.push_back(this);
		n = 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < vcShapes.size(); i++){
			if(vcShapes[i] == 0){
				vcShapes[i] = this;
				n = i;
				break;
			};
		};

		//If an open space wasn't found
		if(n == 0){
			vcShapes.push_back(this);
			n = vcShapes.size() - 1;
		};
	};

	//Initialize variables
	t = _t;		//Type of shape
	x = _x;		//Base coordinates
	y = _y;
	x1 = _x1;	//Vertex coordinates for rectangles/kites
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
	x3 = _x3;
	y3 = _y3;
	x4 = _x4;
	y4 = _y4;
	w = _w;		//Width
	h = _h;		//Height
	a = _a;		//Angle for every shape other than circles
	s = _s;		//Sides for polygons
	r = _r;		//Radius for circles/polygons
};

bool xyHitTest(xyShape* a, xyShape* b){
	//Get which kind of shapes are passed
	switch(a->t){
		case shVect:
			switch(b->t){
				case shVect:
					return xyHitTestVV(a, b);
					break;
			};
			break;

		case shCirc:
			switch(b->t){
				case shCirc:
					return xyHitTestCC(a, b);
					break;
			};
			break;

		case shLine:
			switch(b->t){
				case shLine:
					return xyHitTestLL(a, b);
					break;
			};
			break;
	};

	return 0;
};

// Vector to vector
bool xyHitTestVV(xyShape* a, xyShape* b){
	return a-> x == b->x && a->y == b->y;
};

//Circle to circle
bool xyHitTestCC(xyShape* a, xyShape* b){
	return xyDistance(a->x, a->y, b->x, b->y) <= a->r + b->r;
};

//Line to line
bool xyHitTestLL(xyShape* a, xyShape* b){
	//Get denominator
	float den = ((b->y2 - b->y1) * (a->x2 - a->x1)) - ((b->x2 - b->x1) * (a->y2 - a->y1));
	if(den == 0) return 1;

	//Get whether intersect lies within segments
	float ua = (((b->x2 - b->x1) * (a->y1 - b->y1)) - ((b->y2 - b->y1) * (a->x1 - b->x1))) / den;
	float ub = (((a->x2 - a->x1) * (a->y1 - b->y1)) - ((a->y2 - a->y1) * (a->x1 - b->x1))) / den;
	if((ua < 0) || (ua > 1) || (ub < 0) || (ub > 1)) return 1;

	//If everything checks out, return true
	return 1;
};

//Circle to line
bool xyHitTestCL(xyShape* a, xyShape* b){
	//Transform local coordinates
	float p1x = b->x1 - a->x;
	float p1y = b->y1 - a->y;
	float p2x = b->x2 - a->y;
	float p2y = b->y2 - a->y;
	float pmx = p2x - p1x;
	float pmy = p2y - p1y;

	float pa = (pmx * pmx) + (pmy * pmy);
	float pb = 2 * ((pmx * p1x) + (pmy - p1y));
	float pc = (p1x * p1x) + (p1y * p1y) - (a->r * a->r);
	float delta = pb * pb - (4 * pa * pc);

	return (delta >= 0);
};

//Point in shape
bool xyPointInShape(float x, float y, xyShape* a){
	switch(a->t){
		case shVect:
		case shLine:
			return 0;
			break;
		case shCirc:
			return xyDistance(x, y, a->x, a->y) <= a->r;
			break;
		case shTria:
			break;
	};

	return 0;
};

//Shape area
float xyGetArea(xyShape* a){
	switch(a->t){
		case shVect:
		case shLine:
			return 0;
			break;
		case shRect:
			return a->w * a->h;
			break;
		case shCirc:
			return pi * (a->r*a->r);
			break;
		case shPoly:
			return (((a->r*a->r) * a->s) * sin(360 / a->s));
			break;
		case shKite:
			return (a->w * a->h) / 2;
			break;
		case shTria:
			float la, lb, lc, pr;

			//Get length of each side
			la = xyDistance(a->x1, a->y1, a->x2, a->y2);
			lb = xyDistance(a->x2, a->y2, a->x3, a->y3);
			lc = xyDistance(a->x1, a->y1, a->x3, a->y3);
			pr = (la + lb + lc) / 2;

			//Calculate the area
			return std::sqrt(pr * (pr - la) * (pr - lb) * (pr - lc));
	};

	return 0;
};

void xyDrawShape(Uint32 a, bool fill){
	//Get what type of shape is being drawn
	switch(a->t){
		case shVect:
			SDL_RenderDrawPoint(gvRender, a->x, a->y);
			break;
		case shLine:
			SDL_RenderDrawLine(gvRender, a->x1, a->y1, a->x2, a->y2);
			break;
		case shCirc:
			break;
		case shRect:
      break;
	};
};
