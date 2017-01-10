/*============*\
| MATHS HEADER |
\*============*/

#ifndef _XYMATHS_H_
#define _XYMATHS_H_

#include "main.h"
#include "global.h"
#include "shapes.h"

float xyDistance(float x1, float y1, float x2, float y2);	//Distance between two points
int xyRandomInt(int mx);	//Generate a random integer
float xyRandomFloat(float mx);	//Generate a random float
int xyWrap(int x, int l, int u); //Wrap an integer

#endif
