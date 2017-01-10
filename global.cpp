/*=============*\
| GLOBAL SOURCE |
\*=============*/

#include "global.h"

bool gvQuit = 0;
int gvMouseX = 0, gvMouseY = 0;
Uint32 gvScrW = 400, gvScrH = 240;
Uint32 gvWinW = 320, gvWinH = 240;
HSQUIRRELVM gvSquirrel;
FILE *gvLog;
SDL_Window *gvWindow;
SDL_Renderer *gvRender;
SDL_Texture *gvScreen;
int gvError;
Uint32 gvTicks = 0;
char *gvVNo = "v.1.0.1";
const float pi = 3.14159;
bool gvClearScreen = 1;
SDL_Event Event;
vector<SDL_Texture*> vcTextures;
bool gvDebug = 1;
vector<xySprite*> vcSprites;
Uint32 gvBackColor;
Uint32 gvDrawColor;
