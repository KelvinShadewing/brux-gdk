/*=============*\
| GLOBAL HEADER |
\*=============*/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "sprite.h"
#include "text.h"
#include "shapes.h"

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
extern Uint32 gvTicks;
extern Uint32 gvTickLast;
extern Uint32 gvFrames;
extern const char *gvVNo;			//XYRE version number
extern const float pi;				//Pi
extern bool gvClearScreen;			//Whether to clear the screen on update
extern SDL_Event Event;				//Used for event handling
extern std::vector<SDL_Texture*> vcTextures;		//Keeps track of user-created textures
extern bool gvDebug;				//Controls whether or not debug output is printed
extern std::vector<xySprite*> vcSprites;	//std::vector containing all sprite pointers
extern Uint32 gvBackColor;			//Background color
extern Uint32 gvDrawColor;			//Renderer color
extern std::vector<xyFont*> vcFonts;	//Container for fonts
extern std::vector<Mix_Chunk*> vcSounds;	//Container for sounds
extern std::vector<Mix_Music*> vcMusic;	//Container for music
extern std::string gvAppDir;				//Directory Brux is running from
extern std::string gvWorkDir;			//Working directory, default is the game directory
extern const Uint8 *sdlKeys;
extern std::vector<Uint8> keystate;
extern std::vector<Uint8> keylast;
extern Uint32 buttonstate[5];
extern Uint32 buttonlast[5];
extern Sint32 mouseWheelX;
extern Sint32 mouseWheelY;
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
