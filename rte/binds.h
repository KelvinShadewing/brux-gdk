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
SQInteger sqLoadWindowIcon(HSQUIRRELVM v);
SQInteger sqGetFrames(HSQUIRRELVM v);
SQInteger sqGetScreenW(HSQUIRRELVM v);
SQInteger sqGetScreenH(HSQUIRRELVM v);
SQInteger sqGetDisplayH(HSQUIRRELVM v);
SQInteger sqGetDisplayW(HSQUIRRELVM v);
SQInteger sqBruxVersion(HSQUIRRELVM v);
SQInteger sqToggleFullscreen(HSQUIRRELVM v);

//File IO
SQInteger sqImport(HSQUIRRELVM v);
SQInteger sqDoNut(HSQUIRRELVM v);
SQInteger sqDoString(HSQUIRRELVM v);
SQInteger sqFileExists(HSQUIRRELVM v);
SQInteger sqFileWrite(HSQUIRRELVM v);
SQInteger sqFileRead(HSQUIRRELVM v);
SQInteger sqFileAppend(HSQUIRRELVM v);
SQInteger sqGetDir(HSQUIRRELVM v);
SQInteger sqSetDir(HSQUIRRELVM v);
SQInteger sqLsDir(HSQUIRRELVM v);
SQInteger sqIsDir(HSQUIRRELVM v);

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
SQInteger sqNewTexture(HSQUIRRELVM v);
SQInteger sqTextureSetBlendMode(HSQUIRRELVM v);

//Sprites
SQInteger sqSpriteName(HSQUIRRELVM v);
SQInteger sqNewSprite(HSQUIRRELVM v);
SQInteger sqNewSpriteFT(HSQUIRRELVM v);
SQInteger sqDrawSprite(HSQUIRRELVM v);
SQInteger sqDrawSpriteEx(HSQUIRRELVM v);
SQInteger sqDrawSpriteMod(HSQUIRRELVM v);
SQInteger sqDrawSpriteExMod(HSQUIRRELVM v);
SQInteger sqDeleteSprite(HSQUIRRELVM v);
SQInteger sqFindSprite(HSQUIRRELVM v);
SQInteger sqSpriteName(HSQUIRRELVM v);
SQInteger sqSpriteW(HSQUIRRELVM v);
SQInteger sqSpriteH(HSQUIRRELVM v);
SQInteger sqReplaceSprite(HSQUIRRELVM v);
SQInteger sqSpriteSetBlendMode(HSQUIRRELVM v);

//Input
SQInteger sqKeyPress(HSQUIRRELVM v);
SQInteger sqKeyRelease(HSQUIRRELVM v);
SQInteger sqKeyDown(HSQUIRRELVM v);
SQInteger sqKeyPressAny(HSQUIRRELVM v);
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
SQInteger sqPadName(HSQUIRRELVM v);
SQInteger sqPadX(HSQUIRRELVM v);
SQInteger sqPadY(HSQUIRRELVM v);
SQInteger sqPadZ(HSQUIRRELVM v);
SQInteger sqPadH(HSQUIRRELVM v);
SQInteger sqPadV(HSQUIRRELVM v);
SQInteger sqPadR(HSQUIRRELVM v);
SQInteger sqPadL(HSQUIRRELVM v);
SQInteger sqPadAxis(HSQUIRRELVM v);
SQInteger sqPadHatDown(HSQUIRRELVM v);
SQInteger sqPadHatPress(HSQUIRRELVM v);
SQInteger sqPadHatRelease(HSQUIRRELVM v);
SQInteger sqPadButtonDown(HSQUIRRELVM v);
SQInteger sqPadButtonPress(HSQUIRRELVM v);
SQInteger sqPadButtonRelease(HSQUIRRELVM v);
SQInteger sqPadButtonAny(HSQUIRRELVM v);
SQInteger sqPadAxisPress(HSQUIRRELVM v);
SQInteger sqPadAxisRelease(HSQUIRRELVM v);
SQInteger sqKeyChar(HSQUIRRELVM v);

//Maths
SQInteger sqRandomFloat(HSQUIRRELVM v);
SQInteger sqRandomInt(HSQUIRRELVM v);
SQInteger sqDistance2(HSQUIRRELVM v);
SQInteger sqDistance3(HSQUIRRELVM v);
SQInteger sqInDistance2(HSQUIRRELVM v);
SQInteger sqWrap(HSQUIRRELVM v);
SQInteger sqRound(HSQUIRRELVM v);
SQInteger sqCeil(HSQUIRRELVM v);
SQInteger sqFloor(HSQUIRRELVM v);
SQInteger sqPointAngle(HSQUIRRELVM v);
SQInteger sqAbs(HSQUIRRELVM v);
SQInteger sqLenDirX(HSQUIRRELVM v);
SQInteger sqLenDirY(HSQUIRRELVM v);

//Text
SQInteger sqNewFont(HSQUIRRELVM v);
SQInteger sqDrawText(HSQUIRRELVM v);
SQInteger sqChint(HSQUIRRELVM v);

//Audio
SQInteger sqLoadSound(HSQUIRRELVM v);
SQInteger sqLoadMusic(HSQUIRRELVM v);
SQInteger sqPlaySound(HSQUIRRELVM v);
SQInteger sqPlaySoundChannel(HSQUIRRELVM v);
SQInteger sqPlayMusic(HSQUIRRELVM v);
SQInteger sqDeleteSound(HSQUIRRELVM v);
SQInteger sqDeleteMusic(HSQUIRRELVM v);
SQInteger sqStopSound(HSQUIRRELVM v);
SQInteger sqStopChannel(HSQUIRRELVM v);
SQInteger sqStopMusic(HSQUIRRELVM v);
SQInteger sqCheckMusic(HSQUIRRELVM v);
SQInteger sqCheckSound(HSQUIRRELVM v);
SQInteger sqSetMaxChannels(HSQUIRRELVM v);
SQInteger sqPauseMusic(HSQUIRRELVM v);
SQInteger sqResumeMusic(HSQUIRRELVM v);
SQInteger sqMusicPaused(HSQUIRRELVM v);
SQInteger sqFadeMusic(HSQUIRRELVM v);

//SDL_gfx
SQInteger sqDrawCircle(HSQUIRRELVM v);
SQInteger sqDrawRect(HSQUIRRELVM v);
SQInteger sqDrawLine(HSQUIRRELVM v);
SQInteger sqDrawPoint(HSQUIRRELVM v);
SQInteger sqDrawLineWide(HSQUIRRELVM v);

//Shapes
SQInteger sqLineLine(HSQUIRRELVM v);
SQInteger sqLineCircle(HSQUIRRELVM v);
SQInteger sqLinePoint(HSQUIRRELVM v);


#endif
