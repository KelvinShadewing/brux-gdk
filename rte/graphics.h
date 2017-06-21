/*===============*\
| GRAPHICS HEADER |
\*===============*/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "main.h"

SDL_Texture* xyLoadTexture(const char*  path);
void xyClearScreen();
void xyWait(int ticks);
void xySetDrawTarget(Uint32 tex);
void xyResetDrawTarget();
void xyDrawImage(Uint32 tex, float x, float y);
Uint32 xyLoadImage(const char* path, Uint32 key);
void xySetDrawColor(int r, int g, int b, int a);
void xySetDrawColor(Uint32 color);
Uint32 xyLoadImage(const char* path);
Uint32 xyLoadImageKeyed(const char* path, Uint32 key);
void xySetBackgroundColor(Uint32 color);
void xyDeleteImage(Uint32 img);
Uint8 xyGetRed(Uint32 color);
Uint8 xyGetGreen(Uint32 color);
Uint8 xyGetBlue(Uint32 color);

#endif
