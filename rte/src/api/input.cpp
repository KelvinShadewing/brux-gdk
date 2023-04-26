//  Brux - Input API
//  Copyright (C) 2016 KelvinShadewing
//                2023 Vankata453
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

#include "api/input.hpp"

#include "brux/input.hpp"

namespace BruxAPI {

///////////
// INPUT //
///////////

int keyPress(int key) {
	return xyKeyPress(key);
}

int keyDown(int key) {
	return xyKeyDown(key);
}

int keyRelease(int key) {
	return xyKeyRelease(key);
}

int keyPressAny() {
	int key = -1;

	for (int i = 0; i < 322; i++) {
		if (xyKeyPress(i)) {
			key = i;
			break;
		}
	}

	return key;
}

int mouseDown(int button) {
	return xyMouseButton(button);
}

int mousePress(int button) {
	return xyMousePress(button);
}

int mouseRelease(int button) {
	return xyMouseRelease(button);
}

int mouseX() {
	return gvMouseX;
}

int mouseY() {
	return gvMouseY;
}

bool getQuit() {
	return gvQuit;
}

int joyCount() {
	return SDL_NumJoysticks();
}

std::string joyName(int i) {
	return gvPadName[i];
}

int joyX(int i) {
	return gvPadX[i];
}

int joyY(int i) {
	return gvPadY[i];
}

int joyZ(int i) {
	return gvPadZ[i];
}

int joyH(int i) {
	return gvPadH[i];
}

int joyV(int i) {
	return gvPadV[i];
}

int joyR(int i) {
	return gvPadR[i];
}

int joyL(int i) {
	return gvPadL[i];
}

int joyAxis(int i, int j) {
	return gvPadAxis[i][j];
}

bool joyHatDown(int i, int d) {
	return gvPadHat[i] & (1 << (d - 1));
}

bool joyHatPress(int i, int d) {
	return (gvPadHat[i] & (1 << (d - 1))) && !(gvPadHatLast[i] & (1 << (d - 1)));
}

bool joyHatRelease(int i, int d) {
	return !(gvPadHat[i] & (1 << (d - 1))) && (gvPadHatLast[i] & (1 << (d - 1)));
}

int joyButtonDown(int i, int b) {
	return gvPadButton[i][b];
}

int joyButtonPress(int i, int b) {
	return (gvPadButton[i][b] && !gvPadLastButton[i][b]);
}

int joyButtonRelease(int i, int b) {
	return (!gvPadButton[i][b] && gvPadLastButton[i][b]);
}

int joyPressAny(int p) {
	int button = -1;

	for (int i = 0; i < 32; i++) {
		if (gvPadButton[p][i] && !gvPadLastButton[p][i]) {
			button = i;
			break;
		}
	}

	return button;
}

int joyAxisPress(int p, int a, int d) {
	return xyJoyAxisPress(p, a, d);
}

int joyAxisRelease(int p, int a, int d) {
	return xyJoyAxisRelease(p, a, d);
}

std::string keyString() {
	const std::string input = gvInputString;
	gvInputString = ""; // Clean input.
	return input;
}

int mouseWheelX() {
	return ::mouseWheelX;
}

int mouseWheelY() {
	return ::mouseWheelY;
}

} // namespace BruxAPI
