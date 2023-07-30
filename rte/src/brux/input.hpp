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

#include "brux/global.hpp"

bool xyKeyPress(Uint32 key); // Check if a key was pressed
bool xyKeyRelease(Uint32 key); // Check if a key was released
bool xyKeyDown(Uint32 key); // Check if a key is down
bool xyMouseArea(SDL_Rect* area); // Check if the mouse is in an area
bool xyMouseButton(int button); // Check if a mouse button is down
bool xyMousePress(int button);
bool xyMouseRelease(int button);
void xyInitInput(); // Set up input
int xyJoyAxisPress (int pad, int axis, int dz); // Check if an axis was pressed
int xyJoyAxisRelease (int pad, int axis, int dz); // Check if an axis was released

#endif
