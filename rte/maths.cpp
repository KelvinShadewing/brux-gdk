/*============*\
| MATHS SOURCE |
\*============*/


#include "main.h"
#include "global.h"
#include "maths.h"

float xyDistance(float x1, float y1, float x2, float y2) {
	//2D distance formula
	float xd = (float)(x1 - x2);
	float yd = (float)(y1 - y2);

	return sqrt((xd * xd) + (yd * yd));
};

float xyDistance3(float x1, float y1, float z1, float x2, float y2, float z2) {
	float xd = (float)(x1 - x2);
	float yd = (float)(y1 - y2);
	float zd = (float)(z1 - z2);

	return sqrt((xd * xd) + (yd * yd) + (zd * zd));
};

int xyRandomInt(int mx) {
	int numb = rand();
	numb %= mx;

	return numb;
};

float xyRandomFloat(float mx) {
	float f = rand();
	return (f / (float)RAND_MAX) * mx;
};

float xyWrap(float x, float a0, float a1) {
	float mx = max(a0, a1);
	float mn = min(a0, a1);

	float diff = mx - mn + 1;

	if(x >= 0) return mn + fmodf(x, diff);
	if(x < 0) return mx + fmod(x, diff);
	return 0; //Just so GCC is happy
};

float xyPointAngle(float x1, float y1, float x2, float y2) {
	return atan2(y2 - y1, x2 - x1) * (180 / pi);
};

bool xyPointInBox(float x1, float y1, float x2, float y2, float px, float py) {
	//Get min/max of box in case box is flipped
	float t, b, l, r;
	l = min(x1, x2);
	r = max(x1, x2);
	t = min(y1, y2);
	b = max(y1, y2);

	return px < r && px > l && py < b && py > t;
};

float xyLenDirX(float l, float d) {
	return l * cos(d * pi / 180);
};

float xyLenDirY(float l, float d) {
	return l * sin(d * pi / 180);
};
