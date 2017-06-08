/*==========*\
|INPUT SOURCE|
\*==========*/

#include "input.h"

const Uint8 *sdlKeys;		//Array for storing SDL keystate
vector<Uint8> keystate(322);//Used for tracking key events
vector<Uint8> keylast(322);	//Used for tracking key events

void xyUpdateInput(){
	xyUpdateKeys();
	xyUpdateMouse();
};

bool xyKeyPress(Uint32 key){
	if(key >= 322) return 0;

	return keystate[key] && !keylast[key];
};

bool xyKeyRelease(Uint32 key){
	if(key >= 322) return 0;

	return !keystate[key] && keylast[key];
};

bool xyKeyDown(Uint32 key){
	if(key >= 322) return 0;

	return keystate[key];
};

void xyUpdateKeys(){
	keylast = keystate;
	SDL_PumpEvents();
	for(int i = 0; i < 322; i++){
		keystate[i] = sdlKeys[i];
	};
};

bool xyMouseArea(SDL_Rect* area){
	return((gvMouseX >= area->x) && (gvMouseX <= area->x + area->w) && (gvMouseY >= area->y) && (gvMouseY <= area->y + area->h));
};

bool xyMouseButton(int button){
	if(button >= 1 && button <= 3) return(Event.button.button == button);
	else return 0;
};

void xyUpdateMouse(){
	//Update mouse coords
	SDL_GetMouseState(&gvMouseX, &gvMouseY);

	//Divide by scale
	float sx, sy;
	SDL_RenderGetScale(gvRender, &sx, &sy);

	if(sx == 0) sx = 1;
	if(sy == 0) sy = 1;

	gvMouseX /= sx;
	gvMouseY /= sy;
};

void xyInitInput(){
	sdlKeys = SDL_GetKeyboardState(0);
	for(int i = 0; i < 322; i++){
		keystate[i] = 0;
		keylast[i] = 0;
	};
	xyPrint(0, "Input initialized.");
};
