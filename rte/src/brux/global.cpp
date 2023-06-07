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
| GLOBAL SOURCE |
\*=============*/

#include "brux/main.hpp"
#include "brux/sprite.hpp"
#include "brux/global.hpp"
#include "brux/text.hpp"
#include "brux/shapes.hpp"

int __stack_chk_guard = 0xdeadbeef;
bool gvQuit = 0;
int gvMouseX = 0, gvMouseY = 0;
Uint32 gvScrW = 320, gvScrH = 240;
Uint32 gvWinW = 320, gvWinH = 240;
HSQUIRRELVM gvSquirrel;
std::ofstream gvLog;
SDL_Window *gvWindow;
SDL_Renderer *gvRender;
SDL_Texture *gvScreen;
int gvError;
#ifdef USE_CHRONO_STEADY_CLOCK
std::chrono::time_point<std::chrono::steady_clock> gvTicks = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> gvTickLast = std::chrono::steady_clock::now();
#else
Uint32 gvTicks = 1;
Uint32 gvTickLast = 0;
#endif
float gvFPS = 0;
Uint32 gvMaxFPS = 60;
Uint32 gvFrames = 0;
const char *gvVNo = "v.0.3.1";
const float pi = 3.14159265f;
bool gvClearScreen = 1;
SDL_Event Event;
std::vector<SDL_Texture*> vcTextures;
std::vector<std::string> vcTextureNames;
bool gvDebug = 1;
std::vector<xySprite*> vcSprites;
std::vector<xyFont*> vcFonts;
Uint32 gvBackColor;
Uint32 gvDrawColor;
std::string gvAppDir;
std::string gvWorkDir;
const Uint8 *sdlKeys;
std::vector<Uint8> keystate(322);
std::vector<Uint8> keylast(322);
Uint32 buttonstate[5];
Uint32 buttonlast[5];
int mouseWheelX = 0;
int mouseWheelY = 0;
Uint8 fileMax = 128;
std::vector<xyShape*> gvShape;
std::string gvInputString;
int gvMixChannels;
int gvVolumeMusic = 128;
int gvVolumeSound = 128;
int gvDrawTarget = 0;

//Gamepad
SDL_Joystick* gvGamepad[8] = {0};
int gvPadButton[8][32] = {0};
int gvPadLastButton[8][32] = {0};
int gvPadAxis[8][10] = {0};
int gvPadLastAxis[8][10] = {0};
int gvPadX[8] = {0};
int gvPadY[8] = {0};
int gvPadZ[8] = {0};
int gvPadH[8] = {0};
int gvPadV[8] = {0};
int gvPadR[8] = {0};
int gvPadL[8] = {0};
std::string gvPadName[8] = {"?"};
int gvPadHat[8] = {0};
int gvPadHatLast[8] = {0};
