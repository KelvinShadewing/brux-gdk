/*=============*\
| GLOBAL HEADER |
\*=============*/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "sprite.h"
#include "text.h"

extern bool gvQuit;					//Let's the game know when to quit
extern int gvMouseX, gvMouseY;		//Mouse coordinates
extern Uint32 gvScrW, gvScrH;		//Screen resolution
extern Uint32 gvWinW, gvWinH;		//Window resolution
extern HSQUIRRELVM gvSquirrel;		//Squirrel VM
extern ofstream gvLog;				//Output log
extern SDL_Window *gvWindow;		//Main window
extern SDL_Renderer *gvRender;		//Main renderer
extern SDL_Texture *gvScreen;		//Main screen texture
extern int gvError;					//Error code
extern float gvFPS;
extern Uint32 gvMaxFPS;
extern Uint32 gvTicks;
extern Uint32 gvTickLast;
extern const char *gvVNo;			//XYRE version number
extern const float pi;				//Pi
extern bool gvClearScreen;			//Whether to clear the screen on update
extern SDL_Event Event;				//Used for event handling
extern vector<SDL_Texture*> vcTextures;		//Keeps track of user-created textures
extern bool gvDebug;				//Controls whether or not debug output is printed
extern vector<xySprite*> vcSprites;	//Vector containing all sprite pointers
extern Uint32 gvBackColor;			//Background color
extern Uint32 gvDrawColor;			//Renderer color
extern vector<xyFont*> vcFonts;	//Container for fonts
extern vector<Mix_Chunk*> vcSounds;	//Container for sounds
extern vector<Mix_Music*> vcMusic;	//Container for music
extern string gvAppDir;				//Directory Brux is running from
extern string gvWorkDir;			//Working directory, default is the game directory
extern const Uint8 *sdlKeys;
extern vector<Uint8> keystate;
extern vector<Uint8> keylast;
extern Uint32 buttonstate[5];
extern Uint32 buttonlast[5];
extern Uint8 fileMax;
extern SDL_Joystick* gvGamepad[8];


#endif
