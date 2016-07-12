/*=============*\
| GLOBAL HEADER |
\*=============*/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "main.h"
#include "sprite.h"
#include "shapes.h"

extern bool gvQuit;					//Let's the game know when to quit
extern int gvMouseX, gvMouseY;		//Mouse coordinates
extern Uint32 gvScrW, gvScrH;		//Screen resolution
extern Uint32 gvWinW, gvWinH;		//Window resolution
extern HSQUIRRELVM gvSquirrel;		//Squirrel VM
extern FILE *gvLog;					//Output log
extern SDL_Window *gvWindow;		//Main window
extern SDL_Renderer *gvRender;		//Main renderer
extern SDL_Texture *gvScreen;		//Main screen texture
extern int gvError;					//Error code
extern Uint32 gvTicks, gvSeconds;	//Timer variables
extern Uint32 gvMinutes, gvHours;
extern char *gvVNo;				 //XYRE version number
extern const float pi;				//Pi
extern bool gvClearScreen;			//Whether to clear the screen on update
extern SDL_Event Event;				//Used for event handling
extern vector<SDL_Texture*> vcTextures;		//Keeps track of user-created textures
extern bool gvDebug;				//Controls whether or not debug output is printed
extern vector<xySprite*> vcSprites;	//Vector containing all sprite pointers
extern Uint32 gvBackColor;			//Background color
extern vector<xyShape*> vcShapes;			//Shape index

#endif
