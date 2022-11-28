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
std::ofstream gvLog;
SDL_Window *gvWindow;
SDL_Renderer *gvRender;
SDL_Texture *gvScreen;
int gvError;
Uint32 gvTicks = 1;
Uint32 gvTickLast = 0;
float gvFPS = 0;
Uint32 gvMaxFPS = 60;
Uint32 gvFrames = 0;
const char *gvVNo = "v.0.2.11";
const float pi = 3.14159265;
bool gvClearScreen = 1;
SDL_Event Event;
std::vector<SDL_Texture*> vcTextures;
bool gvDebug = 1;
std::vector<xySprite*> vcSprites;
std::vector<xyFont*> vcFonts;
Uint32 gvBackColor;
Uint32 gvDrawColor;
std::vector<Mix_Chunk*> vcSounds;
std::vector<Mix_Music*> vcMusic;
std::string gvAppDir;
std::string gvWorkDir;
const Uint8 *sdlKeys;
std::vector<Uint8> keystate(322);
std::vector<Uint8> keylast(322);
Uint32 buttonstate[5];
Uint32 buttonlast[5];
Sint32 mouseWheelX = 0;
Sint32 mouseWheelY = 0;
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
