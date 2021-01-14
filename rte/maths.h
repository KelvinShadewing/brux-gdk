/*============*\
| MATHS HEADER |
\*============*/

#ifndef _XYMATHS_H_
#define _XYMATHS_H_

float xyDistance(float x1, float y1, float x2, float y2);	//Distance between two points
int xyRandomInt(int mx);	//Generate a random integer
float xyRandomFloat(float mx);	//Generate a random float
float xyWrap(float x,float a0,float a1); //Wrap an integer
float xyPointAngle(float x1, float y1, float x2, float y2); //Get the angle between two points
bool xyPointInBox(float x1, float y1, float x2, float y2, float px, float py);
float xyLenDirX(float l, float d);
float xyLenDirY(float l, float d);

#endif
