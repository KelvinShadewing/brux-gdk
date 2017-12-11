/*=============*\
| SHAPES SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "maths.h"
#include "shapes.h"

//////////
// LINE //
//////////

////////////
// CIRCLE //
////////////

bool xyHitTest(Circle *a, Circle *b){
	return xyDistance(a->x, a->y, b->x, b->y) <= a->w + b->w;
};

///////////////
// RECTANGLE //
///////////////
