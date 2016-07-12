/*==========*\
|INPUT HEADER|
\*==========*/

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "global.h"

void xyUpdateInput();				//Update all inputs
bool xyKeyPress(Uint32 key);		//Check if a key was pressed
bool xyKeyRelease(Uint32 key);		//Check if a key was released
bool xyKeyDown(Uint32 key);			//Check if a key is down
void xyUpdateKeys();				//Update key state
bool xyMouseArea(SDL_Rect* area);	//Check if the mouse is in an area
bool xyMouseButton(int button);		//Check if a mouse button is down
void xyUpdateMouse();				//Update mouse state
void xyInitInput();					//Set up input

#endif