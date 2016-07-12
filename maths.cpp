/*===========*\
| MATH SOURCE |
\*===========*/

#include "maths.h"

float xyDistance(float x1, float y1, float x2, float y2){
	//2D distance formula
	float xd = abs((float)(x1 - x2));
	float yd = abs((float)(y1 - y2));

	return sqrt((xd * xd) + (yd * yd));
};

float xyDistance(xyCir *c1, xyCir *c2){
	//Distance between two circles from the edge. May produce negative results.
	return (xyDistance(c1->x, c1->y, c2->x, c2->y) - c1->r) - c2->r;
};

int xyRandomInt(int max){
	int numb = rand();
	numb %= max;

	return numb;
};

float xyRandomFloat(float max){
	float numb = rand();
	while(numb > max) numb -= max;

	return numb;
};

int xyWrap(int N, int L, int H){
  H=H-L+1; return (N-L+(N<L)*H)%H+L;
}
