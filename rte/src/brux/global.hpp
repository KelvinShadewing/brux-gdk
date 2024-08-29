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

#include <simplesquirrel/vm.hpp>

#include "brux/main.hpp"
#include "brux/shapes.hpp"
#include "brux/sprite.hpp"
#include "brux/text.hpp"

#define pi 3.14159265f
#define OS_WINDOWS 0
#define OS_LINUX 1
#define OS_ANDROID 2
#define OS_MAC 3
#define OS_DINGUX 4

extern int __stack_chk_guard;
extern bool gvQuit;
extern int gvMouseX;
extern int gvMouseY;
extern uint32_t gvScrW, gvScrH;
extern uint32_t gvWinW, gvWinH;
extern ssq::VM gvSquirrel;
extern std::ofstream gvLog;
extern uint32_t gvError;
extern float gvFPS;
extern uint32_t gvMaxFPS;
#ifdef USE_CHRONO_STEADY_CLOCK
extern std::chrono::time_point<std::chrono::steady_clock> gvTicks;
extern std::chrono::time_point<std::chrono::steady_clock> gvTickLast;
#else
extern uint32_t gvTicks;
extern uint32_t gvTickLast;
#endif
extern uint32_t gvFrames;
extern const char *gvVNo;
extern bool gvClearScreen;
extern bool gvDebug;
extern std::vector<xySprite*> vcSprites;
extern uint32_t gvBackColor;
extern uint32_t gvDrawColor;
extern std::vector<xyFont*> vcFonts;
extern std::string gvAppDir;
extern std::string gvWorkDir;
extern const uint8_t *sdlKeys;
extern std::vector<uint8_t> keystate;
extern std::vector<uint8_t> keylast;
extern uint32_t buttonstate[5];
extern uint32_t buttonlast[5];
extern uint32_t mouseWheelX;
extern uint32_t mouseWheelY;
extern uint8_t fileMax;
extern std::vector<xyShape*> gvShape;
extern std::string gvInputString;
extern uint32_t gvMixChannels;
extern uint32_t gvVolumeMusic;
extern uint32_t gvVolumeSound;
extern uint32_t gvDrawTarget;
extern bool gvUpdateDeprecationWarningShown;
extern bool gvDidError;
extern bool gvQuitRequested;

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
