//  Brux - Input
//  Copyright (C) 2016 KelvinShadewing
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

/*==========*\
|INPUT SOURCE|
\*==========*/

#include "brux/input.hpp"

#include <simplesquirrel/vm.hpp>

#include "brux/global.hpp"

bool xyKeyPress(uint32_t key) {
	// Ignore invalid keys

	if (key >= 322) {
		return false;
	}

	return keystate[key] && !keylast[key];
}

int xyKeyPressAny() {
	int key = -1;

	for (int i = 0; i < 322; i++) {
		if (xyKeyPress(i)) {
			key = i;
			break;
		}
	}

	return key;
}

bool xyKeyRelease(uint32_t key) {
	// Ignore invalid keys
	
	if (key >= 322) {
		return false;
	}

	return !keystate[key] && keylast[key];
}

bool xyKeyDown(uint32_t key) {
	// Ignore invalid keys
	
	if (key >= 322) {
		return false;
	}

	return keystate[key];
}

int xyMouseX() {
	return gvMouseX;
}

int xyMouseY() {
	return gvMouseY;
}

bool xyMouseArea(SDL_Rect* area) {
	return ((gvMouseX >= area->x) && (gvMouseX <= area->x + area->w) && (gvMouseY >= area->y) && (gvMouseY <= area->y + area->h));
}

bool xyMouseButton(int button) {
	// Ignore invalid buttons

	if (button < 0 || button > 4) {
		return false;
	}

	return buttonstate[button];
}

bool xyMousePress(int button) {
	// Ignore invalid buttons

	if (button < 0 || button > 4) {
		return false;
	}

	return buttonstate[button] && !buttonlast[button];
}

bool xyMouseRelease(int button) {
	// Ignore invalid buttons

	if (button < 0 || button > 4) {
		return false;
	}

	return !buttonstate[button] && buttonlast[button];
}

void xyInitInput() {
	SDL_GetMouseState(&gvMouseX, &gvMouseY);

	for (int i = 0; i < 5; i++) {
		buttonstate[i] = 0;
		buttonlast[i] = 0;
	}

	sdlKeys = SDL_GetKeyboardState(0);

	for (int i = 0; i < 322; i++) {
		keystate[i] = 0;
		keylast[i] = 0;
	}

	xyPrint("Input initialized.");
}

int xyJoyAxisPress(int pad, int axis, int dz) {
	// Ignore invalid inputs

	if (pad >= 8 || pad < 0 || axis >= 10 || axis < 0) {
		return 0;
	}

	// If the axis is further from 0 than the dead zone but wasn't before
	// Return 1 if positive or -1 if negative

	if (gvPadAxis[pad][axis] > dz && gvPadLastAxis[pad][axis] <= dz) {
		return 1;
	}

	if (gvPadAxis[pad][axis] < -dz && gvPadLastAxis[pad][axis] >= -dz) {
		return -1;
	}
	
	// Return 0 if axis has moved into deadzone

	return 0;
}

int xyJoyAxisRelease(int pad, int axis, int dz) {
	// Ignore invalid inputs
	
	if (pad >= 8 || pad < 0 || axis >= 10 || axis < 0) {
		return 0;
	}

	// If the axis has returned to the dead zone,
	// return 1 if positive or -1 if negative

	if (gvPadAxis[pad][axis] < dz && gvPadLastAxis[pad][axis] >= dz) {
		return 1;
	}

	if (gvPadAxis[pad][axis] > -dz && gvPadLastAxis[pad][axis] <= -dz) {
		return -1;
	}

	// Return 0 if axis has moved into deadzone

	return 0;
}

std::string xyJoyName(int i) {
	return gvPadName[i];
}

int xyJoyX(int i) {
	return gvPadX[i];
}

int xyJoyY(int i) {
	return gvPadY[i];
}

int xyJoyZ(int i) {
	return gvPadZ[i];
}

int xyJoyH(int i) {
	return gvPadH[i];
}

int xyJoyV(int i) {
	return gvPadV[i];
}

int xyJoyR(int i) {
	return gvPadR[i];
}

int xyJoyL(int i) {
	return gvPadL[i];
}

int xyJoyAxis(int i, int j) {
	return gvPadAxis[i][j];
}

bool xyJoyHatDown(int i, int d) {
	return gvPadHat[i] & (1 << (d - 1));
}

bool xyJoyHatPress(int i, int d) {
	return (gvPadHat[i] & (1 << (d - 1))) && !(gvPadHatLast[i] & (1 << (d - 1)));
}

bool xyJoyHatRelease(int i, int d) {
	return !(gvPadHat[i] & (1 << (d - 1))) && (gvPadHatLast[i] & (1 << (d - 1)));
}

int xyJoyButtonDown(int i, int b) {
	return gvPadButton[i][b];
}

int xyJoyButtonPress(int i, int b) {
	return (gvPadButton[i][b] && !gvPadLastButton[i][b]);
}

int xyJoyButtonRelease(int i, int b) {
	return (!gvPadButton[i][b] && gvPadLastButton[i][b]);
}

int xyJoyPressAny(int p) {
	int button = -1;

	for (int i = 0; i < 32; i++) {
		if (gvPadButton[p][i] && !gvPadLastButton[p][i]) {
			button = i;
			break;
		}
	}

	return button;
}

bool xyGetQuit() {
	return gvQuit || gvQuitRequested;
}

void xyQuitGame() {
	gvQuitRequested = true;
}

std::string xyKeyString() {
	const std::string input = gvInputString;
	gvInputString = ""; // Clean input.
	return input;
}

int xyMouseWheelX() {
	return mouseWheelX;
}

int xyMouseWheelY() {
	return mouseWheelY;
}


void xyRegisterInputAPI(ssq::VM& vm) {
	vm.addFunc("keyPress", xyKeyPress); // Doc'd
	vm.addFunc("keyDown", xyKeyDown); // Doc'd
	vm.addFunc("keyRelease", xyKeyRelease); // Doc'd
	vm.addFunc("keyPressAny", xyKeyPressAny); // Doc'd
	vm.addFunc("mouseDown", xyMouseButton); // Doc'd
	vm.addFunc("mousePress", xyMousePress); // Doc'd
	vm.addFunc("mouseRelease", xyMouseRelease); // Doc'd
	vm.addFunc("mouseX", xyMouseX); // Doc'd
	vm.addFunc("mouseY", xyMouseY); // Doc'd
	vm.addFunc("getQuit", xyGetQuit); // Doc'd
	vm.addFunc("quitGame", xyQuitGame); // Doc'd
	vm.addFunc("joyCount", SDL_NumJoysticks); // Doc'd
	vm.addFunc("joyName", xyJoyName); // Doc'd
	vm.addFunc("joyX", xyJoyX); // Doc'd
	vm.addFunc("joyY", xyJoyY); // Doc'd
	vm.addFunc("joyZ", xyJoyZ); // Doc'd
	vm.addFunc("joyH", xyJoyH); // Doc'd
	vm.addFunc("joyV", xyJoyV); // Doc'd
	vm.addFunc("joyR", xyJoyR); // Doc'd
	vm.addFunc("joyL", xyJoyL); // Doc'd
	vm.addFunc("joyAxis", xyJoyAxis); // Doc'd
	vm.addFunc("joyHatDown", xyJoyHatDown); // Doc'd
	vm.addFunc("joyHatPress", xyJoyHatPress); // Doc'd
	vm.addFunc("joyHatRelease", xyJoyHatRelease); // Doc'd
	vm.addFunc("joyButtonPress", xyJoyButtonPress); // Doc'd
	vm.addFunc("joyButtonDown", xyJoyButtonDown); // Doc'd
	vm.addFunc("joyButtonRelease", xyJoyButtonRelease); // Doc'd
	vm.addFunc("joyPressAny", xyJoyPressAny); // Doc'd
	vm.addFunc("joyAxisPress", xyJoyAxisPress); // Doc'd
	vm.addFunc("joyAxisRelease", xyJoyAxisRelease); // Doc'd
	vm.addFunc("keyString", xyKeyString); // Doc'd
	vm.addFunc("mouseWheelX", xyMouseWheelX); // Doc'd
	vm.addFunc("mouseWheelY", xyMouseWheelY); // Doc'd
}
