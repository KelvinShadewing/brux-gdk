/*===============*\
| BINDINGS HEADER |
\*===============*/

#ifndef _BINDINGS_H_
#define _BINDINGS_H_

//These functions are wrappers used to interact
//with Squirrel so that the main versions can
//still be used internally by the RTE.

//Main
SQInteger sqUpdate(HSQUIRRELVM v);
SQInteger sqGetOS(HSQUIRRELVM v);
SQInteger sqGetTicks(HSQUIRRELVM v);
SQInteger sqGetFPS(HSQUIRRELVM v);
SQInteger sqSetFPS(HSQUIRRELVM v);
SQInteger sqSetWindowTitle(HSQUIRRELVM v);

//File IO
SQInteger sqImport(HSQUIRRELVM v);
SQInteger sqDoNut(HSQUIRRELVM v);
SQInteger sqFileExists(HSQUIRRELVM v);
SQInteger sqFileWrite(HSQUIRRELVM v);
SQInteger sqFileRead(HSQUIRRELVM v);
SQInteger sqGetDir(HSQUIRRELVM v);
SQInteger sqSetDir(HSQUIRRELVM v);

//Graphics
SQInteger sqWait(HSQUIRRELVM v);
SQInteger sqClearScreen(HSQUIRRELVM v);
SQInteger sqSetDrawTarget(HSQUIRRELVM v);
SQInteger sqDrawImage(HSQUIRRELVM v);
SQInteger sqSetDrawColor(HSQUIRRELVM v);
SQInteger sqSetBackgroundColor(HSQUIRRELVM v);
SQInteger sqLoadImage(HSQUIRRELVM v);
SQInteger sqLoadImageKeyed(HSQUIRRELVM v);
SQInteger sqSetScalingFilter(HSQUIRRELVM v);
SQInteger sqSetResolution(HSQUIRRELVM v);

//Sprites
SQInteger sqSpriteName(HSQUIRRELVM v);
SQInteger sqNewSprite(HSQUIRRELVM v);
SQInteger sqDrawSprite(HSQUIRRELVM v);
SQInteger sqDrawSpriteEx(HSQUIRRELVM v);
SQInteger sqDeleteSprite(HSQUIRRELVM v);

//Input
SQInteger sqKeyPress(HSQUIRRELVM v);
SQInteger sqKeyRelease(HSQUIRRELVM v);
SQInteger sqKeyDown(HSQUIRRELVM v);
SQInteger sqResetDrawTarget(HSQUIRRELVM v);
SQInteger sqLoadImage(HSQUIRRELVM v);
SQInteger sqDrawImage(HSQUIRRELVM v);
SQInteger sqMouseDown(HSQUIRRELVM v);
SQInteger sqMousePress(HSQUIRRELVM v);
SQInteger sqMouseRelease(HSQUIRRELVM v);
SQInteger sqGetQuit(HSQUIRRELVM v);
SQInteger sqMouseX(HSQUIRRELVM v);
SQInteger sqMouseY(HSQUIRRELVM v);
SQInteger sqGetPads(HSQUIRRELVM v);

//Maths
SQInteger sqRandomFloat(HSQUIRRELVM v);
SQInteger sqRandomInt(HSQUIRRELVM v);
SQInteger sqDistance2(HSQUIRRELVM v);
SQInteger sqWrap(HSQUIRRELVM v);
SQInteger sqRound(HSQUIRRELVM v);
SQInteger sqCeil(HSQUIRRELVM v);
SQInteger sqFloor(HSQUIRRELVM v);
SQInteger sqPointAngle(HSQUIRRELVM v);

//Text
SQInteger sqNewFont(HSQUIRRELVM v);
SQInteger sqDrawText(HSQUIRRELVM v);

//Audio
SQInteger sqLoadSound(HSQUIRRELVM v);
SQInteger sqLoadMusic(HSQUIRRELVM v);
SQInteger sqPlaySound(HSQUIRRELVM v);
SQInteger sqPlayMusic(HSQUIRRELVM v);
SQInteger sqDeleteSound(HSQUIRRELVM v);
SQInteger sqDeleteMusic(HSQUIRRELVM v);

//SDL_gfx
SQInteger sqDrawCircle(HSQUIRRELVM v);

#endif
