//  Brux - Graphics
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

/*===============*\
| GRAPHICS HEADER |
\*===============*/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "brux/main.hpp"

SDL_Texture* xyLoadTexture(const std::string& path);
void xyClearScreen();
void xyWait(int ticks);
void xySetDrawTarget(Uint32 tex);
void xyResetDrawTarget();
void xyDrawImage(Uint32 tex, float x, float y);
void xyDrawImageEx(Uint32 tex, float x, float y, float angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha, Uint32 color);
Uint32 xyLoadImage(const std::string& path, Uint32 key);
void xySetDrawColor(int r, int g, int b, int a);
void xySetDrawColor(SQInteger color);
Uint32 xyLoadImage(const std::string& path);
Uint32 xyLoadImageKeyed(const std::string& path, Uint32 key);
void xySetBackgroundColor(Uint32 color);
void xyDeleteImage(Uint32 img);
Uint8 xyGetRed(Uint32 color);
Uint8 xyGetGreen(Uint32 color);
Uint8 xyGetBlue(Uint32 color);
Uint8 xyGetAlpha(Uint32 color);
Uint32 xyNewTexture(Uint32 w, Uint32 h);

#endif
