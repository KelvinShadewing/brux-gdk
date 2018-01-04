/*============*\
| MATHS SOURCE |
\*============*/


#include "main.h"
#include "global.h"
#include "maths.h"

float xyDistance(float x1, float y1, float x2, float y2){
	//2D distance formula
	float xd = abs((float)(x1 - x2));
	float yd = abs((float)(y1 - y2));

	return sqrt((xd * xd) + (yd * yd));
};

int xyRandomInt(int mx){
	int numb = rand();
	numb %= mx;

	return numb;
};

float xyRandomFloat(float mx){
	float numb = rand();
	while(numb > mx) numb -= mx;

	return numb;
};

int xyWrap(int N, int L, int H){
  H=H-L+1; return (N-L+(N<L)*H)%H+L;
}

float xyPointAngle(float x1, float y1, float x2, float y2){
	return atan2(y2 - y1, x2 - x1) * (180 / pi);
};

bool xyPointInBox(float x1, float y1, float x2, float y2, float px, float py){
	//Get min/max of box in case box is flipped
	float t, b, l, r;
	l = min(x1, x2);
	r = max(x1, x2);
	t = min(y1, y2);
	b = max(y1, y2);

	return px < r && px > l && py < b && py > t;
};
