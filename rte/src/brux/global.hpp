//  Brux - Globals
//  Copyright (C) 2016 KelvinShadewing
//  Copyright (C) 2023 hexaheximal
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

/*=============*\
| GLOBAL HEADER |
\*=============*/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "brux/main.hpp"
#include "brux/sprite.hpp"
#include "brux/text.hpp"
#include "brux/shapes.hpp"

#define pi 3.14159265f
#define OS_WINDOWS 0
#define OS_LINUX 1
#define OS_ANDROID 2
#define OS_MAC 3
#define OS_DINGUX 3

extern int __stack_chk_guard;
extern bool gvQuit;
extern int gvMouseX;
extern int gvMouseY;
extern Uint32 gvScrW, gvScrH;
extern Uint32 gvWinW, gvWinH;
extern HSQUIRRELVM gvSquirrel;
extern std::ofstream gvLog;
extern SDL_Window *gvWindow;
extern SDL_Renderer *gvRender;
extern SDL_Texture *gvScreen;
extern Uint32 gvError;
extern float gvFPS;
extern Uint32 gvMaxFPS;
#ifdef USE_CHRONO_STEADY_CLOCK
extern std::chrono::time_point<std::chrono::steady_clock> gvTicks;
extern std::chrono::time_point<std::chrono::steady_clock> gvTickLast;
#else
extern Uint32 gvTicks;
extern Uint32 gvTickLast;
#endif
extern Uint32 gvFrames;
extern const char *gvVNo;
extern bool gvClearScreen;
extern std::vector<SDL_Texture*> vcTextures;
extern std::vector<std::string> vcTextureNames;
extern bool gvDebug;
extern std::vector<xySprite*> vcSprites;
extern Uint32 gvBackColor;
extern Uint32 gvDrawColor;
extern std::vector<xyFont*> vcFonts;
extern std::string gvAppDir;
extern std::string gvWorkDir;
extern const Uint8 *sdlKeys;
extern std::vector<Uint8> keystate;
extern std::vector<Uint8> keylast;
extern Uint32 buttonstate[5];
extern Uint32 buttonlast[5];
extern Uint32 mouseWheelX;
extern Uint32 mouseWheelY;
extern Uint8 fileMax;
extern std::vector<xyShape*> gvShape;
extern std::string gvInputString;
extern Uint32 gvMixChannels;
extern Uint32 gvVolumeMusic;
extern Uint32 gvVolumeSound;
extern Uint32 gvDrawTarget;

// Gamepad

extern SDL_Joystick* gvGamepad[8];
extern int gvPadButton[8][32];
extern int gvPadLastButton[8][32];
extern int gvPadX[8];
extern int gvPadY[8];
extern int gvPadZ[8];
extern int gvPadH[8];
extern int gvPadV[8];
extern int gvPadR[8];
extern int gvPadL[8];
extern int gvPadAxis[8][10];
extern int gvPadLastAxis[8][10];
extern std::string gvPadName[8];
extern int gvPadHat[8];
extern int gvPadHatLast[8];

#endif
