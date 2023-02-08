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
