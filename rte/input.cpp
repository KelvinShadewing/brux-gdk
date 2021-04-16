/*==========*\
|INPUT SOURCE|
\*==========*/

#include "input.h"

bool xyKeyPress(Uint32 key) {
	if(key >= 322) return 0;

	return keystate[key] && !keylast[key];
};

bool xyKeyRelease(Uint32 key) {
	if(key >= 322) return 0;

	return !keystate[key] && keylast[key];
};

bool xyKeyDown(Uint32 key) {
	if(key >= 322) return 0;

	return keystate[key];
};

bool xyMouseArea(SDL_Rect* area) {
	return((gvMouseX >= area->x) && (gvMouseX <= area->x + area->w) && (gvMouseY >= area->y) && (gvMouseY <= area->y + area->h));
};

bool xyMouseButton(int button) {
	if(button >= 0 && button <= 4) return buttonstate[button];
	else return 0;
};

bool xyMousePress(int button) {
	if(button < 0 || button > 4) return 0;
	return buttonstate[button] && !buttonlast[button];
};

bool xyMouseRelease(int button) {
	if(button < 0 || button > 4) return 0;
	return !buttonstate[button] && buttonlast[button];
};

void xyInitInput() {
	SDL_GetMouseState(&gvMouseX, &gvMouseY);
	for(int i = 0; i < 5; i++) {
		buttonstate[i] = 0;
		buttonlast[i] = 0;
	};
	sdlKeys = SDL_GetKeyboardState(0);
	for(int i = 0; i < 322; i++) {
		keystate[i] = 0;
		keylast[i] = 0;
	};
	xyPrint(0, "Input initialized.");
};
