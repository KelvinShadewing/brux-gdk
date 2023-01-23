/*=============================================*\
| PROJECT: Brux Game Runtime Environment        |
| AUTHOR: Nick Kovacs                           |
| DATE: 8-15-15                                 |
| DESC: Runtime environment used for            |
|  games and applications created using         |
|  the Brux game framework.                     |
| LICENSE: GNU Affero General Public License v3 |
\*=============================================*/

/*===========*\
| MAIN SOURCE |
\*===========*/

//Main headers
#include "main.h"
#include "core.h"
#include "global.h"
#include "input.h"
#include "graphics.h"
#include "maths.h"
#include "fileio.h"
#include "binds.h"
#include "text.h"
#include "audio.h"


/////////////////
//MAIN FUNCTION//
/////////////////
#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
int main(int argc, char* argv[]) {
#ifdef __EMSCRIPTEN__
	EM_ASM(
		console.log(FS.readdir("/"));
		console.log(FS.readdir("/bin"));
		FS.chdir('/bin');
	);
#endif
	//Initiate everything
	if(xyInit() == 0) {
		xyPrint(0, "Failed to initiate Brux!");
		xyEnd();
		return 1;
	}

	//Process arguments
	std::string xygapp = "";
	std::string curarg = "";
	for(int i = 0; i < argc; i++) {
		//Print each argument and process them
		curarg = argv[i];
		xyPrint(0, curarg.c_str());

	//The first argument is just the
	//command to invoke the runtime,
	//so skip it.
		if(i != 0) {
			//Input file
			//If the file is long enough
			if(curarg.length() > 4) {
				//If the input is a Squirrel file
				if(curarg.substr(curarg.find_last_of('.')) == ".sq" || curarg.substr(curarg.find_last_of('.')) == ".nut" || curarg.substr(curarg.find_last_of('.')) == ".brx"){
					//Check that the file really exists
					if(xyLegacyFileExists(curarg)) {
						//All checks pass, assign the file
						char tmpstr[64];
						xygapp = curarg;
						size_t found = xygapp.find_last_of("/\\");
						gvWorkDir = xygapp.substr(0, found);
						chdir(gvWorkDir.c_str());
						const std::string curdir = xyGetDir();
						xyPrint(0, "Working directory: %s", curdir.c_str());
					}
				}
			}
		//Other arguments

		if(curarg == "-f" || curarg == "--fullscreen") SDL_SetWindowFullscreen(gvWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
	}

	SDL_ShowCursor(0);

	//Mount the current working directory.
	xyFSMount(xyGetDir(), true);

	//Set the current write directory to a default for Brux.
	//Can be changed later by the game.
	xySetWriteDir(xyGetPrefDir("brux", "brux"));

	//Run app
	if(xygapp != "") {
		xyPrint(0, "Running %s...", xygapp.c_str());
		sqstd_dofile(gvSquirrel, xygapp.c_str(), 0, 1);
	}
	else {
		if(xyFileExists("test.nut")) sqstd_dofile(gvSquirrel, "test.nut", 0, 1);
		else if(xyFileExists("game.brx")) sqstd_dofile(gvSquirrel, "game.brx", 0, 1);
	}

	//End game
	xyEnd();

	return 0;
}

///////////////////
//OTHER FUNCTIONS//
///////////////////

//Handles initialization of SDL2 and Squirrel
int xyInit() {
	//Initiate log file
	remove("log.txt");
	gvLog.open("log.txt", ios_base::out);

	//Print opening message
	xyPrint(0, "\n/========================\\\n| BRUX GAME RUNTIME LOG |\n\\========================/\n\n");
	xyPrint(0, "Initializing program...\n\n");

	//Initialize the file system (PhysFS)
	xyPrint(0, "Initializing file system...");
	xyFSInit();

	//Initiate SDL
	SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
#ifdef __EMSCRIPTEN__
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
#else
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
#endif
		xyPrint(0, "Failed to initialize! %s", SDL_GetError());
		return 0;
	}

	//Create window
	gvWindow = SDL_CreateWindow("BRUX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gvScrW, gvScrH, SDL_WINDOW_RESIZABLE);
	if(gvWindow == 0) {
		xyPrint(0, "Window could not be created! SDL Error: %s\n", SDL_GetError());
		return 0;
	} else {
		//Create renderer for window
		gvRender = SDL_CreateRenderer(gvWindow, -1, SDL_RENDERER_ACCELERATED);
		if(gvRender == 0) {
			xyPrint(0, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return 0;
		} else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(gvRender, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				xyPrint(0, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return 0;
			}

			//Set up the viewport
			SDL_Rect screensize;
			screensize.x = 0;
			screensize.y = 0;
			screensize.w = gvScrW;
			screensize.h = gvScrH;
			SDL_RenderSetViewport(gvRender, &screensize);
			SDL_RenderSetLogicalSize(gvRender, gvScrW, gvScrH);
		}
	}

	//Initialize audio
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		xyPrint(0, "SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
		return 0;
	}

	//Get channel count
	gvMixChannels = Mix_AllocateChannels(-8);

	//Initialize input
	xyInitInput();

	xyPrint(0, "SDL initialized successfully!");

	//Initiate Squirrel
	gvSquirrel = sq_open(1024);


	sq_setprintfunc(gvSquirrel, xyPrint, xyPrint);
	sq_pushroottable(gvSquirrel);

	sqstd_register_iolib(gvSquirrel);
	sqstd_register_systemlib(gvSquirrel);
	sqstd_register_mathlib(gvSquirrel);
	sqstd_register_stringlib(gvSquirrel);

	xyBindAllFunctions(gvSquirrel);

	/*Error handler does not seem to print compile-time errors. I haven't
	been able to figure out why, as the same code works in my other apps,
	and is taken from the sq.c example included with Squirrel.*/
	sqstd_seterrorhandlers(gvSquirrel);

	xyPrint(0, "Squirrel initialized successfully!");

	//Initiate other
	vcTextures.push_back(0);
	vcSprites.push_back(0);
	vcSounds.push_back(0);
	vcMusic.push_back(0);
	vcFonts.push_back(0);

	xyLoadCore(); //Squirrel-side definitions
	xyLoadActors();

	xyPrint(0, "\n================\n");

	//Return success
	return 1;
};

void xyEnd(){

	xyPrint(0, "\n\n================\n");

	//Cleanup all resources
	xyPrint(0, "Cleaning up all resources...");
	xyPrint(0, "Cleaning textures...");
	for(int i = 0; i < vcTextures.size(); i++) {
		xyDeleteImage(i);
	}

	xyPrint(0, "Cleaning sprites...");
	for(int i = 0; i < vcSprites.size(); i++) {
		delete vcSprites[i];
	}

	xyPrint(0, "Cleaning sounds...");
	for(int i = 0; i < vcSounds.size(); i++) {
		xyDeleteSound(i);
	}

	xyPrint(0, "Cleaning music...");
	for(int i = 0; i < vcMusic.size(); i++) {
		xyDeleteMusic(i);
	}
	xyPrint(0, "Finished cleanup.");

	//Close Squirrel
	xyPrint(0, "Closing Squirrel...");
	SQInteger garbage = sq_collectgarbage(gvSquirrel);
	xyPrint(0, "Collected %i junk obects.", garbage);
	sq_pop(gvSquirrel, 1);
	sq_close(gvSquirrel);

	//Close SDL
	xyPrint(0, "Closing SDL...");
	SDL_DestroyRenderer(gvRender);
	SDL_DestroyWindow(gvWindow);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	//Destroy the file system (PhysFS)
	xyPrint(0, "Closing file system...");
	xyFSDeinit();

	//Close log file
	xyPrint(0, "System closed successfully!");
	gvLog.close();
};

void xyPrint(HSQUIRRELVM v, const SQChar *s, ...) {
	va_list argv;
	va_start(argv, s);
	SQChar buffer[1024*1024] = _SC("");
	vsnprintf(buffer, sizeof(buffer), s, argv);
	va_end(argv);
	cout << buffer << endl;
	gvLog << buffer << endl;
};

void xyBindFunc(HSQUIRRELVM v, SQFUNCTION func, const SQChar *key) {
	sq_pushroottable(v);
	sq_pushstring(v, key, -1);
	sq_newclosure(v, func, 0);
	sq_newslot(v, -3, false);
	sq_pop(v, 1);
};

void xyBindFunc(HSQUIRRELVM v, SQFUNCTION func, const SQChar *key, SQInteger nParams, const SQChar* sParams) {
	//Binds a function from C++ to a word in
	//Squirrel to be called from scripts.
	sq_pushroottable(v);
	sq_pushstring(v, key, -1);
	sq_newclosure(v, func, 0);
	sq_setparamscheck(v, nParams, sParams);
	sq_newslot(v, -3, false);
	sq_pop(v, 1);
};

void xyBindAllFunctions(HSQUIRRELVM v) {
	//Binds all functions needed by the game.
	//Calling this function again will fix any
	//overwritten embedded functions, but the
	//user can still redefine the function to
	//call this anyway, so no safety net is
	//even attempted. If they screw it up, they
	//will jusy have to learn.

	//Main
	xyPrint(0, "Embedding main...");
	xyBindFunc(v, sqUpdate, "update"); //Doc'd
	xyBindFunc(v, sqGetOS, "getOS"); //Doc'd
	xyBindFunc(v, sqWait, "wait", 2, ".n"); //Doc'd
	xyBindFunc(v, sqDoNut, "donut", 2, ".s"); //Doc'd
	xyBindFunc(v, sqGetTicks, "getTicks"); //Doc'd
	xyBindFunc(v, sqGetFPS, "getFPS"); //Doc'd
	xyBindFunc(v, sqSetFPS, "setFPS", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqSetWindowTitle, "setWindowTitle", 2, ".s"); //Doc'd
	xyBindFunc(v, sqLoadWindowIcon, "setWindowIcon", 2, ".s"); //Doc'd
	xyBindFunc(v, sqGetFrames, "getFrames"); //Doc'd
	xyBindFunc(v, sqBruxVersion, "bruxVersion"); //Doc'd
	xyBindFunc(v, sqToggleFullscreen, "toggleFullscreen"); //Doc'd

	//Graphics
	xyPrint(0, "Embedding graphics...");
	xyBindFunc(v, sqSetDrawTarget, "setDrawTarget", 2, ". n"); //Doc'd
	xyBindFunc(v, sqGetDrawTarget, "getDrawTarget"); //Doc'd
	xyBindFunc(v, sqClearScreen, "clearScreen"); //Doc'd
	xyBindFunc(v, sqResetDrawTarget, "resetDrawTarget");
	xyBindFunc(v, sqDrawImageEx, "drawImageEx", 9, ". n|b n|b n|b n|b n|b n|b n|b n|b");
	xyBindFunc(v, sqSetDrawColor, "setDrawColor", 2, ".n"); //Doc'd
	xyBindFunc(v, sqLoadImage, "loadImage", 2, ".s"); //Doc'd
	xyBindFunc(v, sqLoadImageKeyed, "loadImageKey", 3, ".sn|b"); //Doc'd
	xyBindFunc(v, sqDrawImage, "drawImage", 4, ".i|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqSetBackgroundColor, "setBackgroundColor", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqSetScaling, "setScaling", 2, ".n");
	xyBindFunc(v, sqSetScalingFilter, "setScalingFilter", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqSetResolution, "setResolution", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawCircle, "drawCircle", 5, ".n|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawRect, "drawRec", 6, ".n|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawRect, "drawRect", 6, ".n|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawPoint, "drawPoint", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawLine, "drawLine", 5, ".n|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawLineWide, "drawLineWide", 6, ".n|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqNewTexture, "newTexture", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqGetScreenW, "screenW"); //Doc'd
	xyBindFunc(v, sqGetScreenH, "screenH"); //Doc'd
	xyBindFunc(v, sqGetWindowW, "windowW");
	xyBindFunc(v, sqGetWindowH, "windowH");
	xyBindFunc(v, sqGetDisplayW, "displayW"); //Doc'd
	xyBindFunc(v, sqGetDisplayH, "displayH"); //Doc'd
	xyBindFunc(v, sqTextureSetBlendMode, "textureSetBlendMode", 3, ".n|bn|b"); //Doc'd

	//Sprites
	xyPrint(0, "Embedding sprites...");
	xyBindFunc(v, sqSpriteName, "spriteName", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqNewSprite, "newSprite", 8, ".si|bi|bi|bi|bi|bi|b"); //Doc'd
	xyBindFunc(v, sqNewSpriteFT, "newSpriteFT", 8, ".i|bi|bi|bi|bi|bi|bi|b");
	xyBindFunc(v, sqDrawSpriteEx, "drawSpriteEx", 10, ".i|bn|bn|bn|bn|bi|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawSpriteMod, "drawSpriteMod", 6, ".i|bn|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawSpriteExMod, "drawSpriteExMod", 11, ".i|bn|bn|bn|bn|bi|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDeleteSprite, "deleteSprite", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqFindSprite, "findSprite", 2, ".s"); //Doc'd
	xyBindFunc(v, sqSpriteW, "spriteW", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqSpriteH, "spriteH", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqReplaceSprite, "replaceSprite", 9, ".i|bsi|bi|bi|bi|bi|bi|b");
	xyBindFunc(v, sqSpriteSetBlendMode, "spriteSetBlendMode", 3, ".n|bn|b"); //Doc'd

	//Input
	xyPrint(0, "Embedding input...");
	xyBindFunc(v, sqKeyPress, "keyPress", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqKeyRelease, "keyRelease", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqKeyDown, "keyDown", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqKeyPressAny, "anyKeyPress"); //Doc'd
	xyBindFunc(v, sqMouseDown, "mouseDown", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqMousePress, "mousePress", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqMouseRelease, "mouseRelease", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqMouseX, "mouseX"); //Doc'd
	xyBindFunc(v, sqMouseY, "mouseY"); //Doc'd
	xyBindFunc(v, sqGetQuit, "getQuit"); //Doc'd
	xyBindFunc(v, sqGetPads, "joyCount"); //Doc'd
	xyBindFunc(v, sqPadName, "joyName", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadAxis, "joyAxis", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadHatDown, "joyHatDown", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadHatPress, "joyHatPress", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadHatRelease, "joyHatRelease", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadButtonDown, "joyButtonDown", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadButtonPress, "joyButtonPress", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadButtonRelease, "joyButtonRelease", 3, ".i|bi|b"); //Doc'd
	xyBindFunc(v, sqPadButtonAny, "anyJoyPress", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadX, "joyX", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadY, "joyY", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadZ, "joyZ", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadH, "joyH", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadV, "joyV", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadR, "joyR", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadL, "joyL", 2, ".i|b"); //Doc'd
	xyBindFunc(v, sqPadAxisPress, "joyAxisPress", 4, ".i|bi|bi|b"); //Doc'd
	xyBindFunc(v, sqPadAxisRelease, "joyAxisRelease", 4, ".i|bi|bi|b"); //Doc'd
	xyBindFunc(v, sqKeyChar, "keyString"); //Doc'd
	xyBindFunc(v, sqMouseWheelX, "mouseWheelX"); //Doc'd
	xyBindFunc(v, sqMouseWheelY, "mouseWheelY"); //Doc'd

	//Maths
	xyPrint(0, "Embedding maths...");
	xyBindFunc(v, sqRandomFloat, "randFloat", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqRandomInt, "randInt", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqDistance2, "distance2", 5, ".n|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDistance3, "distance3", 7, ".n|bn|bn|bn|bn|bn|b");
	xyBindFunc(v, sqInDistance2, "inDistance2", 6, ".n|bn|bn|bn|bn|b");
	xyBindFunc(v, sqWrap, "wrap", 4, ".n|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqRound, "round", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqCeil, "ceil", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqFloor, "floor", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqPointAngle, "pointAngle", 5, ".n|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqAbs, "abs", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqLenDirX, "lendirX", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqLenDirY, "lendirY", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqBinStr, "binstr", 2, ".n|b"); //Doc'd

	//Text
	xyPrint(0, "Embedding text...");
	xyBindFunc(v, sqNewFont, "newFont", 6, ".n|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqDrawText, "drawText", 5, ".n|bn|bn|bs"); //Doc'd
	xyBindFunc(v, sqChint, "chint", 2, ".i|b"); //Doc'd

	//File IO
	xyPrint(0, "Embedding file I/O...");
	xyBindFunc(v, sqImport, "import", 2, ".s");
	xyBindFunc(v, sqDoString, "dostr", 2, ".s"); //Doc'd
	xyBindFunc(v, sqMount, "mount", 3, ".sb");
	xyBindFunc(v, sqUnmount, "unmount", 2, ".s");
	xyBindFunc(v, sqGetDir, "getdir"); //Doc'd
	xyBindFunc(v, sqGetWriteDir, "getWriteDir");
	xyBindFunc(v, sqGetPrefDir, "getPrefDir", 3, ".ss");
	xyBindFunc(v, sqSetWriteDir, "setWriteDir", 2, ".s");
	xyBindFunc(v, sqCreateDir, "createDir", 2, ".s");
	xyBindFunc(v, sqFileRead, "fileRead", 2, ".s"); //Doc'd
	xyBindFunc(v, sqFileWrite, "fileWrite", 3, ".ss"); //Doc'd
	xyBindFunc(v, sqFileAppend, "fileAppend", 3, ".ss"); //Doc'd
	xyBindFunc(v, sqFileExists, "fileExists", 2, ".s"); //Doc'd
	xyBindFunc(v, sqFileDelete, "fileDelete", 2, ".s");
	xyBindFunc(v, sqDecodeJSON, "jsonRead", 2, ".s"); //Doc'd
	xyBindFunc(v, sqLsDir, "lsdir", 2, ".s"); //Doc'd
	xyBindFunc(v, sqIsDir, "isdir", 2, ".s"); //Doc'd

	//Audio
	xyPrint(0, "Embedding audio...");
	xyBindFunc(v, sqLoadMusic, "loadMusic", 2, ".s"); //Doc'd
	xyBindFunc(v, sqLoadSound, "loadSound", 2, ".s"); //Doc'd
	xyBindFunc(v, sqPlaySound, "playSound", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqPlaySoundChannel, "playSoundChannel", 4, ".n|bn|bn|b");
	xyBindFunc(v, sqPlayMusic, "playMusic", 3, ".n|bn|b"); //Doc'd
	xyBindFunc(v, sqDeleteSound, "deleteSound", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqDeleteMusic, "deleteMusic", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqStopSound, "stopSound", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqStopChannel, "stopChannel", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqStopMusic, "stopMusic"); //Doc'd
	xyBindFunc(v, sqCheckMusic, "checkMusic"); //Doc'd
	xyBindFunc(v, sqCheckSound, "checkSound", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqSetMaxChannels, "setMaxChannels", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqPauseMusic, "pauseMusic"); //Doc'd
	xyBindFunc(v, sqResumeMusic, "resumeMusic"); //Doc'd
	xyBindFunc(v, sqMusicPaused, "musicPaused"); //Doc'd
	xyBindFunc(v, sqFadeMusic, "fadeMusic", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqSetMusicVolume, "setMusicVolume", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqSetSoundVolume, "setSoundVolume", 2, ".n|b"); //Doc'd
	xyBindFunc(v, sqGetMusicVolume, "getMusicVolume"); //Doc'd
	xyBindFunc(v, sqGetSoundVolume, "getSoundVolume"); //Doc'd

	//Shapes
	xyBindFunc(v, sqLineLine, "hitLineLine", 9, ".n|bn|bn|bn|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqLineCircle, "hitLineCircle", 8, ".n|bn|bn|bn|bn|bn|bn|b"); //Doc'd
	xyBindFunc(v, sqLinePoint, "hitLinePoint", 7, ".n|bn|bn|bn|bn|bn|b"); //Doc'd
};

void xyUpdate() {

	//Update last button state
	for(int i = 0; i < 5; i++) {
		buttonlast[i] = buttonstate[i];
	};

	mouseWheelX = 0;
	mouseWheelY = 0;

	//Reset event-related globals
	gvQuit = 0;

	//Poll events
	while(SDL_PollEvent(&Event)) {
		//Quit
		if(Event.type == SDL_QUIT) gvQuit = 1;

		//Mouse button
		if(Event.type == SDL_MOUSEBUTTONDOWN) {
			if(Event.button.button == SDL_BUTTON_LEFT) buttonstate[0] = 1;
			if(Event.button.button == SDL_BUTTON_MIDDLE) buttonstate[1] = 1;
			if(Event.button.button == SDL_BUTTON_RIGHT) buttonstate[2] = 1;
			if(Event.button.button == SDL_BUTTON_X1) buttonstate[3] = 1;
			if(Event.button.button == SDL_BUTTON_X2) buttonstate[4] = 1;
		}

		if(Event.type == SDL_MOUSEBUTTONUP) {
			if(Event.button.button == SDL_BUTTON_LEFT) buttonstate[0] = 0;
			if(Event.button.button == SDL_BUTTON_MIDDLE) buttonstate[1] = 0;
			if(Event.button.button == SDL_BUTTON_RIGHT) buttonstate[2] = 0;
			if(Event.button.button == SDL_BUTTON_X1) buttonstate[3] = 0;
			if(Event.button.button == SDL_BUTTON_X2) buttonstate[4] = 0;
		}

		if(Event.type == SDL_MOUSEWHEEL) {
			mouseWheelX = Event.wheel.x;
			mouseWheelY = Event.wheel.y;
		}

		if(Event.type == SDL_TEXTINPUT) {
			gvInputString = Event.text.text;
		}
	}

	//Update screen
	SDL_RenderPresent(gvRender);
	Uint32 olddraw = gvDrawColor;
	xySetDrawColor(gvBackColor);
	SDL_RenderClear(gvRender);
	xySetDrawColor(olddraw);
	if(SDL_BYTEORDER == SDL_LIL_ENDIAN) gvDrawColor = SDL_Swap32(gvDrawColor);

	//Update input
	keylast = keystate;
	SDL_PumpEvents();
	for(int i = 0; i < 322; i++) {
		keystate[i] = sdlKeys[i];
	}

	SDL_GetMouseState(&gvMouseX, &gvMouseY);

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 32; j++) {
			gvPadLastButton[i][j] = gvPadButton[i][j];
		};

		if(SDL_JoystickGetAttached(gvGamepad[i])) {
			gvPadHatLast[i] = gvPadHat[i];
			gvPadHat[i] = SDL_JoystickGetHat(gvGamepad[i], 0);
			for(int j = 0; j < 10; j++){
				gvPadLastAxis[i][j] = gvPadAxis[i][j];
				gvPadAxis[i][j] = SDL_JoystickGetAxis(gvGamepad[i], j);
			};
			for(int j = 0; j < 32; j++){
				gvPadLastButton[i][j] = gvPadButton[i][j];
				gvPadButton[i][j] = SDL_JoystickGetButton(gvGamepad[i], j);
			};
			gvPadX[i] = SDL_JoystickGetAxis(gvGamepad[i], 0);
			gvPadY[i] = SDL_JoystickGetAxis(gvGamepad[i], 1);
			gvPadZ[i] = SDL_JoystickGetAxis(gvGamepad[i], 2);
			gvPadH[i] = SDL_JoystickGetAxis(gvGamepad[i], 3);
			gvPadV[i] = SDL_JoystickGetAxis(gvGamepad[i], 4);
			gvPadR[i] = (SDL_JoystickGetAxis(gvGamepad[i], 5) + 32768) / 2;
			gvPadL[i] = (SDL_JoystickGetAxis(gvGamepad[i], 2) + 32768) / 2;
			gvPadName[i] = SDL_JoystickName(gvGamepad[i]);
		} else {
			gvPadHatLast[i] = gvPadHat[i];
			gvPadHat[i] = 0;

			for(int j = 0; j < 10; j++) {
				gvPadAxis[i][j] = 0;
			}

			for(int j = 0; j < 32; j++) {
				gvPadLastButton[i][j] = gvPadButton[i][j];
				gvPadButton[i][j] = 0;
			}

			gvPadX[i] = 0;
			gvPadY[i] = 0;
			gvPadZ[i] = 0;
			gvPadH[i] = 0;
			gvPadV[i] = 0;
			gvPadR[i] = 0;
			gvPadL[i] = 0;
			gvPadName[i] = "?";
		}
	}

	//Divide by scale
	float sx, sy;
	SDL_RenderGetScale(gvRender, &sx, &sy);

	if(sx == 0) sx = 1;
	if(sy == 0) sy = 1;

	gvMouseX /= sx;
	gvMouseY /= sy;

	//Gamepad
	//Check each pad
	for(int i = 0; i < 8; i++) {
		if(SDL_NumJoysticks() > i) gvGamepad[i] = SDL_JoystickOpen(i);
	}

	//Wait for FPS limit
	//Update ticks counter for FPS
	gvTicks = std::chrono::steady_clock::now();

	std::chrono::duration<float> fLength = gvTicks - gvTickLast;
	std::chrono::duration<float> max_delay = std::chrono::duration<float>(1.0f / gvMaxFPS);
	if (fLength < max_delay) {
		if (gvMaxFPS != 0) std::this_thread::sleep_for((max_delay - fLength) - std::chrono::duration<float>(0.0001f)); //SDL_Delay(max_delay - fLength);
	}

	//Calculate time since previous tick and adjust framerate
	std::chrono::duration<float> timeSince = std::chrono::steady_clock::now() - gvTickLast;
	gvFPS = 1.0f / timeSince.count();

	// Update previous tick and increment frames
	gvTickLast = std::chrono::steady_clock::now();
	gvFrames++;
};

int xyGetOS() {
#ifdef _WIN32
	return 0;
#endif
#ifdef __gnu_linux__
	return 1;
#endif
#ifdef __ANDROID__
	return 2;
#endif
#ifdef __APPLE__
	return 3;
#endif
#ifdef _DINGUX
	return 4;
#endif
};

void __stack_chk_fail(void) {
	xyPrint(0, "Stack smash detected.");
};
