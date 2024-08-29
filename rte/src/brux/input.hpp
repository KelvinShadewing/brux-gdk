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
|INPUT HEADER|
\*==========*/

#ifndef _INPUT_H_
#define _INPUT_H_

#include "brux/main.hpp"

bool xyKeyPress(uint32_t key); // Check if a key was pressed
int xyKeyPressAny(); // Get the next pressed key
bool xyKeyRelease(uint32_t key); // Check if a key was released
bool xyKeyDown(uint32_t key); // Check if a key is down
int xyMouseX(); // Get the mouse cursor X position
int xyMouseY(); // Get the mouse cursor Y position
bool xyMouseArea(SDL_Rect* area); // Check if the mouse is in an area
bool xyMouseButton(int button); // Check if a mouse button is down
bool xyMousePress(int button);
bool xyMouseRelease(int button);
void xyInitInput(); // Set up input
int xyJoyAxisPress (int pad, int axis, int dz); // Check if an axis was pressed
int xyJoyAxisRelease (int pad, int axis, int dz); // Check if an axis was released
std::string xyJoyName(int i);
int xyJoyX(int i);
int xyJoyY(int i);
int xyJoyZ(int i);
int xyJoyH(int i);
int xyJoyV(int i);
int xyJoyR(int i);
int xyJoyL(int i);
int xyJoyAxis(int i, int j);
bool xyJoyHatDown(int i, int d);
bool xyJoyHatPress(int i, int d);
bool xyJoyHatRelease(int i, int d);
int xyJoyButtonDown(int i, int b);
int xyJoyButtonPress(int i, int b);
int xyJoyButtonRelease(int i, int b);
int xyJoyPressAny(int p);
bool xyGetQuit(); // Check if game quit has been requested
void xyQuitGame(); // Request game quit
std::string xyKeyString(); // Get and clear string of last pressed key
int xyMouseWheelX(); // Get mouse wheel X movement
int xyMouseWheelY(); // Get mouse wheel Y movement

void xyRegisterInputAPI(ssq::VM& vm);

#endif
