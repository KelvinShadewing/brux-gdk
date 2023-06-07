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

extern int __stack_chk_guard;
extern bool gvQuit;					//Let's the game know when to quit
extern int gvMouseX, gvMouseY;		//Mouse coordinates
extern Uint32 gvScrW, gvScrH;		//Screen resolution
extern Uint32 gvWinW, gvWinH;		//Window resolution
extern HSQUIRRELVM gvSquirrel;		//Squirrel VM
extern std::ofstream gvLog;				//Output log
extern SDL_Window *gvWindow;		//Main window
extern SDL_Renderer *gvRender;		//Main renderer
extern SDL_Texture *gvScreen;		//Main screen texture
extern int gvError;					//Error code
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
extern const char *gvVNo;			//XYRE version number
extern const float pi;				//Pi
extern bool gvClearScreen;			//Whether to clear the screen on update
extern SDL_Event Event;				//Used for event handling
extern std::vector<SDL_Texture*> vcTextures;		//Keeps track of user-created textures
extern std::vector<std::string> vcTextureNames;
extern bool gvDebug;				//Controls whether or not debug output is printed
extern std::vector<xySprite*> vcSprites;	//std::vector containing all sprite pointers
extern Uint32 gvBackColor;			//Background color
extern Uint32 gvDrawColor;			//Renderer color
extern std::vector<xyFont*> vcFonts;	//Container for fonts

// NOTE: vcSounds, vcMusic, as well as the rest of the audio code specific to SDL2, has been moved to the audio directory and made more portable.

extern std::string gvAppDir;				//Directory Brux is running from
extern std::string gvWorkDir;			//Working directory, default is the game directory
extern const Uint8 *sdlKeys;
extern std::vector<Uint8> keystate;
extern std::vector<Uint8> keylast;
extern Uint32 buttonstate[5];
extern Uint32 buttonlast[5];
extern int mouseWheelX;
extern int mouseWheelY;
extern Uint8 fileMax;
extern std::vector<xyShape*> gvShape;
extern std::string gvInputString;
extern int gvMixChannels;
extern int gvVolumeMusic;
extern int gvVolumeSound;
extern int gvDrawTarget;

//Gamepad
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
