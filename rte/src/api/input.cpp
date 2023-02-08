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

int anyKeyPress() {
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

int joyButtonAny(int p) {
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
