/*=============*\
| GLOBAL SOURCE |
\*=============*/

#include "main.h"
#include "sprite.h"
#include "global.h"

bool gvQuit = 0;
int gvMouseX = 0, gvMouseY = 0;
Uint32 gvScrW = 320, gvScrH = 240;
Uint32 gvWinW = 320, gvWinH = 240;
HSQUIRRELVM gvSquirrel;
ofstream gvLog;
SDL_Window *gvWindow;
SDL_Renderer *gvRender;
SDL_Texture *gvScreen;
int gvError;
Uint32 gvTicks = 0;
Uint32 gvTickLast = 0;
float gvFPS = 0;
Uint32 gvMaxFPS = 60;
const char *gvVNo = "v.1.0.0.2";
const float pi = 3.14159265;
bool gvClearScreen = 1;
SDL_Event Event;
vector<SDL_Texture*> vcTextures;
bool gvDebug = 1;
vector<xySprite*> vcSprites;
vector<TTF_Font*> vcFonts;
Uint32 gvBackColor;
Uint32 gvDrawColor;
vector<Mix_Chunk*> vcSounds;
vector<Mix_Music*> vcMusic;
string gvAppDir;
string gvWorkDir;
const Uint8 *sdlKeys;
vector<Uint8> keystate(322);
vector<Uint8> keylast(322);
Uint32 buttonstate[5];
Uint32 buttonlast[5];
