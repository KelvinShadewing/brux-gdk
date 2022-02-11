/*=============*\
| GLOBAL SOURCE |
\*=============*/

#include "main.h"
#include "sprite.h"
#include "global.h"
#include "text.h"
#include "shapes.h"

int __stack_chk_guard = 0xdeadbeef;
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
Uint32 gvTicks = 1;
Uint32 gvTickLast = 0;
float gvFPS = 0;
Uint32 gvMaxFPS = 60;
Uint32 gvFrames = 0;
const char *gvVNo = "v.0.2.2";
const float pi = 3.14159265;
bool gvClearScreen = 1;
SDL_Event Event;
vector<SDL_Texture*> vcTextures;
bool gvDebug = 1;
vector<xySprite*> vcSprites;
vector<xyFont*> vcFonts;
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
Uint8 fileMax = 128;
vector<xyShape*> gvShape;
string gvInputString;
int gvMixChannels;

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
string gvPadName[8] = {"?"};
int gvPadHat[8] = {0};
int gvPadHatLast[8] = {0};
