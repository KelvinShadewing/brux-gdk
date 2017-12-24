/*=============*\
| SHAPES SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "maths.h"
#include "shapes.h"

xyShape::xyShape(int _t, float _x, float _y, float _w, float _h, float _a){
		type = _t;
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		a = _a;
	};


bool xyHitTest(xyShape *a, xyShape *b){
	switch(a->type){
		case _CIR:
			switch(b->type){
				case _CIR:	//Circle to Circle
					return xyDistance(a->x, a->y, b->x, b->y) <= a->w + b->w;
					break;
			};
			break;
	};
};

xyNewLine(float x1, float y1, float x2, float y2){

};
