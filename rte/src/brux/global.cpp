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

// Used to detect a request to close the application

bool gvQuit = false;

// Mouse position

int gvMouseX = 0;
int gvMouseY = 0;

// Game screen size

Uint32 gvScrW = 320;
Uint32 gvScrH = 240;

// Window size

Uint32 gvWinW = 320;
Uint32 gvWinH = 240;

// Squirrel VM

ssq::VM gvSquirrel;

// Log buffer

std::ofstream gvLog;

// SDL2-specific variables

SDL_Window *gvWindow;
SDL_Renderer *gvRender;
SDL_Texture *gvScreen;

// Used for FPS limiting

#ifdef USE_CHRONO_STEADY_CLOCK
std::chrono::time_point<std::chrono::steady_clock> gvTicks = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> gvTickLast = std::chrono::steady_clock::now();
#else
Uint32 gvTicks = 1;
Uint32 gvTickLast = 0;
#endif

// Current game FPS

float gvFPS = 0;

// Maximum FPS limit, this can be changed by the game

Uint32 gvMaxFPS = 60;
Uint32 gvFrames = 0;

// Brux version string

const char *gvVNo = "v0.3.10";

// Should it clear the screen? If true, then the answer is yes.

bool gvClearScreen = 1;

// SDL2-related vectors
// The audio-specific ones have been moved to src/audio/audio_sdl2.cpp though.

std::vector<SDL_Texture*> vcTextures;
std::vector<std::string> vcTextureNames;
std::vector<xySprite*> vcSprites;
std::vector<xyFont*> vcFonts;

// Should it show debug info? If true, then the answer is yes.

bool gvDebug = true;

// Draw colors

Uint32 gvBackColor;
Uint32 gvDrawColor;

// Stores the current working directory that the engine is running from

std::string gvAppDir;

// Stores the current working directory inside of Brux GDK

std::string gvWorkDir;

// misc

const Uint8 *sdlKeys;
std::vector<Uint8> keystate(322);
std::vector<Uint8> keylast(322);
Uint32 buttonstate[5];
Uint32 buttonlast[5];
Uint32 mouseWheelX = 0;
Uint32 mouseWheelY = 0;
Uint8 fileMax = 128;
std::vector<xyShape*> gvShape;
std::string gvInputString;
Uint32 gvMixChannels = 0;
Uint32 gvVolumeMusic = 128;
Uint32 gvVolumeSound = 128;
Uint32 gvDrawTarget = 0;
bool gvUpdateDeprecationWarningShown = false;
bool gvDidError = false;
bool gvQuitRequested = false;

// Gamepad
// NOTE: I don't know why, I don't want to know why, but *somehow* this entirely breaks if we use the Uint32 type for this

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
