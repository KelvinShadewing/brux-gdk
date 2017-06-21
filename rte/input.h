/*==========*\
|INPUT HEADER|
\*==========*/

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "global.h"

bool xyKeyPress(Uint32 key);		//Check if a key was pressed
bool xyKeyRelease(Uint32 key);		//Check if a key was released
bool xyKeyDown(Uint32 key);			//Check if a key is down
bool xyMouseArea(SDL_Rect* area);	//Check if the mouse is in an area
bool xyMouseButton(int button);		//Check if a mouse button is down
bool xyMousePress(int button);
bool xyMouseRelease(int button);
void xyInitInput();					//Set up input

#endif
