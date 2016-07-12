/*===========*\
| MATH HEADER |
\*===========*/

#ifndef _XYMATH_H_
#define _XYMATH_H_

#include "main.h"
#include "global.h"
#include "shapes.h"

float xyDistance(float x1, float y1, float x2, float y2);	//Distance between two points
float xyDistance(xyCir *c1, xyCir *c2);	//Distance between two circles
int xyRandomInt(int max);	//Generate a random integer
float xyRandomFloat(float max);	//Generate a random float
int xyWrap(int x, int l, int u); //Wrap an integer

#endif