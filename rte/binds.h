/*===============*\
| BINDINGS HEADER |
\*===============*/

#ifndef _BINDINGS_H_
#define _BINDINGS_H_

//Main
int sqUpdate(HSQUIRRELVM v);
int sqGetOS(HSQUIRRELVM v);
int sqGetTicks(HSQUIRRELVM v);
int sqGetFPS(HSQUIRRELVM v);
int sqSetFPS(HSQUIRRELVM v);
int sqSetWindowTitle(HSQUIRRELVM v);

//File IO
int sqImport(HSQUIRRELVM v);
int sqFileExists(HSQUIRRELVM v);
int sqGetDir(HSQUIRRELVM v);	//Needs def
int sqSetDir(HSQUIRRELVM v);	//Needs def

//Graphics
int sqWait(HSQUIRRELVM v);
int sqClearScreen(HSQUIRRELVM v);
int sqSetDrawTarget(HSQUIRRELVM v);
int sqDrawImage(HSQUIRRELVM v);
int sqSetDrawColor(HSQUIRRELVM v);
int sqSetBackgroundColor(HSQUIRRELVM v);
int sqLoadImage(HSQUIRRELVM v);
int sqLoadImageKeyed(HSQUIRRELVM v);
int sqSetScalingFilter(HSQUIRRELVM v);
int sqSetResolution(HSQUIRRELVM v);

//Sprites
int sqNewSprite(HSQUIRRELVM v);
int sqDrawSprite(HSQUIRRELVM v);
int sqDrawSpriteEx(HSQUIRRELVM v);
int sqDeleteSprite(HSQUIRRELVM v);

//Input
int sqKeyPress(HSQUIRRELVM v);
int sqKeyRelease(HSQUIRRELVM v);
int sqKeyDown(HSQUIRRELVM v);
int sqResetDrawTarget(HSQUIRRELVM v);
int sqLoadImage(HSQUIRRELVM v);
int sqDrawImage(HSQUIRRELVM v);
int sqMouseX(HSQUIRRELVM v);
int sqMouseY(HSQUIRRELVM v);
int sqMouseDown(HSQUIRRELVM v);
int sqMousePress(HSQUIRRELVM v);
int sqMouseRelease(HSQUIRRELVM v);
int sqGetQuit(HSQUIRRELVM v);

//Maths
int sqRandomFloat(HSQUIRRELVM v);
int sqRandomInt(HSQUIRRELVM v);
int sqDistance2(HSQUIRRELVM v);
int sqWrap(HSQUIRRELVM v);
int sqFloor(HSQUIRRELVM v);
int sqPointAngle(HSQUIRRELVM v);

//Text
int sqDrawText(HSQUIRRELVM v);
int sqOpenFont(HSQUIRRELVM v);
int sqCloseFont(HSQUIRRELVM v);

//Audio
int sqLoadSound(HSQUIRRELVM v);
int sqLoadMusic(HSQUIRRELVM v);
int sqPlaySound(HSQUIRRELVM v);
int sqPlayMusic(HSQUIRRELVM v);
int sqDeleteSound(HSQUIRRELVM v);
int sqDeleteMusic(HSQUIRRELVM v);

//Misc
int sqEmbedTest(HSQUIRRELVM v);

#endif
