/*======================================*\
| PROJECT: Brux Game Runtime Environment |
| AUTHOR: Nick Kovacs                    |
| DATE: 8-15-15                          |
| DESC: Runtime environment used for     |
|  games and applications created using  |
|  the Brux game framework.              |
| LICENSE:GNU General Public License v.3 |
\*======================================*/

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
int main(int argc, char* argv[]) {
	//Initiate everything
	if(xyInit() == 0) {
		xyPrint(0, L"Failed to initiate Brux!");
		xyEnd();
		return 1;
	}

	//Process arguments
	string xygapp = "";
	string curarg = "";
	for(int i = 0; i < argc; i++) {
		//Print each argument and process them
		curarg = argv[i];
		xyPrint(0, towc(curarg.c_str()));

	//The first argument is just the
	//command to invoke the runtime,
	//so skip it.
		if(i != 0) {
			//Input file
			//If the file is long enough
			if(curarg.length() > 4) {
				//If the input is a Squirrel file
				if(curarg.substr(curarg.find_last_of(".")) == ".sq" || curarg.substr(curarg.find_last_of(".")) == ".nut" || curarg.substr(curarg.find_last_of(".")) == ".brx"){
					//Check that the file really exists
					if(xyFileExists(curarg.c_str())) {
						//All checks pass, assign the file
						char tmpstr[64];
						xygapp = curarg.c_str();
						size_t found = xygapp.find_last_of("/\\");
						gvWorkDir = xygapp.substr(0, found);
						chdir(gvWorkDir.c_str());
						xyPrint(0, L"Working directory: %s", getcwd(0,0));
					}
				}
			}
		//Other arguments

		if(curarg == "-f" || curarg == "--fullscreen") SDL_SetWindowFullscreen(gvWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
	}

	SDL_ShowCursor(0);


	//Run app
	if(xygapp != "") {
		xyPrint(0, L"Running %s...", xygapp.c_str());
		sqstd_dofile(gvSquirrel, towc(xygapp.c_str()), 0, 1);
	} else {
		if(xyFileExists("test.nut")) sqstd_dofile(gvSquirrel, L"test.nut", 0, 1);
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
	xyPrint(0, L"\n/========================\\\n| BRUX GAME RUNTIME LOG |\n\\========================/\n\n");
	xyPrint(0, L"Initializing program...\n\n");

	//Initiate SDL
	SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		xyPrint(0, L"Failed to initialize! %s", SDL_GetError());
		return 0;
	}

	//Create window
	gvWindow = SDL_CreateWindow("BRUX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gvScrW, gvScrH, SDL_WINDOW_RESIZABLE);
	if(gvWindow == 0) {
		xyPrint(0, L"Window could not be created! SDL Error: %s\n", SDL_GetError());
		return 0;
	} else {
		//Create renderer for window
		gvRender = SDL_CreateRenderer(gvWindow, -1, SDL_RENDERER_ACCELERATED);
		if(gvRender == 0) {
			xyPrint(0, L"Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return 0;
		} else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(gvRender, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				xyPrint(0, L"SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
		xyPrint(0, L"SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
		return 0;
	}

	//Initialize input
	xyInitInput();

	xyPrint(0, L"SDL initialized successfully!");

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

	xyPrint(0, L"Squirrel initialized successfully!");

	//Initiate other
	vcTextures.push_back(0);
	vcSprites.push_back(0);
	vcSounds.push_back(0);
	vcMusic.push_back(0);
	vcFonts.push_back(0);

	xyLoadCore(); //Squirrel-side definitions
	xyLoadActors();

	xyPrint(0, L"\n================\n");

	//Return success
	return 1;
};

void xyEnd(){

	xyPrint(0, L"\n\n================\n");

	//Cleanup all resources
	xyPrint(0, L"Cleaning up all resources...");
	xyPrint(0, L"Cleaning textures...");
	for(int i = 0; i < vcTextures.size(); i++) {
		xyDeleteImage(i);
	}

	xyPrint(0, L"Cleaning sprites...");
	for(int i = 0; i < vcSprites.size(); i++) {
		delete vcSprites[i];
	}

	xyPrint(0, L"Cleaning sounds...");
	for(int i = 0; i < vcSounds.size(); i++) {
		xyDeleteSound(i);
	}

	xyPrint(0, L"Cleaning music...");
	for(int i = 0; i < vcMusic.size(); i++) {
		xyDeleteMusic(i);
	}
	xyPrint(0, L"Finished cleanup.");

	//Close Squirrel
	xyPrint(0, L"Closing Squirrel...");
	SQInteger garbage = sq_collectgarbage(gvSquirrel);
	xyPrint(0, L"Collected %i junk obects.", garbage);
	sq_pop(gvSquirrel, 1);
	sq_close(gvSquirrel);

	//Close SDL
	xyPrint(0, L"Closing SDL...");
	SDL_DestroyRenderer(gvRender);
	SDL_DestroyWindow(gvWindow);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	//Close log file
	xyPrint(0, L"System closed successfully!");
	gvLog.close();
};

void xyPrint(HSQUIRRELVM v, const SQChar *s, ...) {
	va_list argv;
	va_start(argv, s);
	SQChar buffer[1024*1024] = _SC("");
	char newbuffer[1024*1024];
	char* sbuffer;
	wctomb(newbuffer, *buffer);
	wctomb(sbuffer, *s);
	vsnprintf(newbuffer, sizeof(newbuffer), sbuffer, argv);
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
	xyPrint(0, L"Embedding main...");
	xyBindFunc(v, sqUpdate, L"update");
	xyBindFunc(v, sqGetOS, L"getOS");
	xyBindFunc(v, sqGetTicks, L"getTicks");
	xyBindFunc(v, sqGetFPS, L"getFPS");
	xyBindFunc(v, sqSetFPS, L"setFPS", 2, L".n");
	xyBindFunc(v, sqSetWindowTitle, L"setWindowTitle", 2, L".s");
	xyBindFunc(v, sqLoadWindowIcon, L"setWindowIcon", 2, L".s");
	xyBindFunc(v, sqGetFrames, L"getFrames");
	xyBindFunc(v, sqGetScreenW, L"screenW");
	xyBindFunc(v, sqGetScreenH, L"screenH");
	xyBindFunc(v, sqGetDisplayW, L"displayW");
	xyBindFunc(v, sqGetDisplayH, L"displayH");

	//Graphics
	xyPrint(0, L"Embedding graphics...");
	xyBindFunc(v, sqWait, L"wait", 2, L".n");
	xyBindFunc(v, sqSetDrawTarget, L"setDrawTarget", 2, L".n");
	xyBindFunc(v, sqClearScreen, L"clearScreen");
	xyBindFunc(v, sqResetDrawTarget, L"resetDrawTarget");
	xyBindFunc(v, sqDrawImage, L"drawImage", 4, L".nnn");
	xyBindFunc(v, sqSetDrawColor, L"setDrawColor", 2, L".n");
	xyBindFunc(v, sqLoadImage, L"loadImage", 2, L".s");
	xyBindFunc(v, sqLoadImageKeyed, L"loadImageKey", 3, L".sn");
	xyBindFunc(v, sqDrawImage, L"drawImage", 4, L".inn");
	xyBindFunc(v, sqSetBackgroundColor, L"setBackgroundColor", 2, L".n");
	xyBindFunc(v, sqSetScalingFilter, L"setScalingFilter", 2, L".n|b");
	xyBindFunc(v, sqSetResolution, L"setResolution", 3, L".nn");
	xyBindFunc(v, sqDrawCircle, L"drawCircle", 5, L".nnnn|b");
	xyBindFunc(v, sqDrawRect, L"drawRec", 6, L".nnnnn|b");
	xyBindFunc(v, sqDrawRect, L"drawRect", 6, L".nnnnn|b");
	xyBindFunc(v, sqDrawPoint, L"drawPoint", 3, L".nn");
	xyBindFunc(v, sqDrawLine, L"drawLine", 5, L".nnnn");
	xyBindFunc(v, sqDrawLineWide, L"drawLineWide", 6, L".nnnnn");

	//Sprites
	xyPrint(0, L"Embedding sprites...");
	xyBindFunc(v, sqSpriteName, L"spriteName", 2, L".n");
	xyBindFunc(v, sqNewSprite, L"newSprite", 8, L".siiiiii");
	xyBindFunc(v, sqDrawSprite, L"drawSprite", 5, L".innn");
	xyBindFunc(v, sqDrawSpriteEx, L"drawSpriteEx", 10, L".innnninnn");
	xyBindFunc(v, sqDeleteSprite, L"deleteSprite", 2, L".i");
	xyBindFunc(v, sqFindSprite, L"findSprite", 2, L".s");
	xyBindFunc(v, sqSpriteName, L"spriteName");
	xyBindFunc(v, sqSpriteW, L"spriteW", 2, L".i");
	xyBindFunc(v, sqSpriteH, L"spriteH", 2, L".i");

	//Input
	xyPrint(0, L"Embedding input...");
	xyBindFunc(v, sqKeyPress, L"keyPress", 2, L".n");
	xyBindFunc(v, sqKeyRelease, L"keyRelease", 2, L".n");
	xyBindFunc(v, sqKeyDown, L"keyDown", 2, L".n");
	xyBindFunc(v, sqKeyPressAny, L"anyKeyPress");
	xyBindFunc(v, sqMouseDown, L"mouseDown", 2, L".i");
	xyBindFunc(v, sqMousePress, L"mousePress", 2, L".i");
	xyBindFunc(v, sqMouseRelease, L"mouseRelease", 2, L".i");
	xyBindFunc(v, sqMouseX, L"mouseX");
	xyBindFunc(v, sqMouseY, L"mouseY");
	xyBindFunc(v, sqGetQuit, L"getQuit");
	xyBindFunc(v, sqGetPads, L"joyCount");
	xyBindFunc(v, sqPadName, L"joyName", 2, L".i");
	xyBindFunc(v, sqPadX, L"joyX", 2, L".i");
	xyBindFunc(v, sqPadY, L"joyY", 2, L".i");
	xyBindFunc(v, sqPadZ, L"joyZ", 2, L".i");
	xyBindFunc(v, sqPadH, L"joyH", 2, L".i");
	xyBindFunc(v, sqPadV, L"joyV", 2, L".i");
	xyBindFunc(v, sqPadR, L"joyR", 2, L".i");
	xyBindFunc(v, sqPadL, L"joyL", 2, L".i");
	xyBindFunc(v, sqPadAxis, L"joyAxis", 3, L".ii");
	xyBindFunc(v, sqPadHatDown, L"joyHatDown", 3, L".ii");
	xyBindFunc(v, sqPadHatPress, L"joyHatPress", 3, L".ii");
	xyBindFunc(v, sqPadHatRelease, L"joyHatRelease", 3, L".ii");
	xyBindFunc(v, sqPadButtonDown, L"joyButtonDown", 3, L".ii");
	xyBindFunc(v, sqPadButtonPress, L"joyButtonPress", 3, L".ii");
	xyBindFunc(v, sqPadButtonRelease, L"joyButtonRelease", 3, L".ii");
	xyBindFunc(v, sqPadButtonAny, L"anyJoyPress", 2, L".i");

	//Maths
	xyPrint(0, L"Embedding maths...");
	xyBindFunc(v, sqRandomFloat, L"randFloat", 2, L".n");
	xyBindFunc(v, sqRandomInt, L"randInt", 2, L".n");
	xyBindFunc(v, sqDistance2, L"distance2", 5, L".nnnn");
	xyBindFunc(v, sqWrap, L"wrap", 4, L".nnn");
	xyBindFunc(v, sqRound, L"round", 2, L".n");
	xyBindFunc(v, sqCeil, L"ceil", 2, L".n");
	xyBindFunc(v, sqFloor, L"floor", 2, L".n");
	xyBindFunc(v, sqPointAngle, L"pointAngle", 5, L".nnnn");
	xyBindFunc(v, sqAbs, L"abs", 2, L".n");
	xyBindFunc(v, sqLenDirX, L"lendirX", 3, L".nn");
	xyBindFunc(v, sqLenDirY, L"lendirY", 3, L".nn");

	//Text
	xyPrint(0, L"Embedding text...");
	xyBindFunc(v, sqNewFont, L"newFont", 6, L".nnnnn");
	xyBindFunc(v, sqDrawText, L"drawText", 5, L".nnns");
	xyBindFunc(v, sqChint, L"chint", 2, L".i");

	//File IO
	xyPrint(0, L"Embedding file I/O...");
	xyBindFunc(v, sqFileExists, L"fileExists", 2, L".s");
	xyBindFunc(v, sqImport, L"import", 2, L".s");
	xyBindFunc(v, sqDoNut, L"donut", 2, L".s");
	xyBindFunc(v, sqDoString, L"dostr", 2, L".s");
	xyBindFunc(v, sqDecodeJSON, L"jsonRead", 2, L".s");
	xyBindFunc(v, sqGetDir, L"getdir");
	xyBindFunc(v, sqSetDir, L"chdir", 2, L".s");
	xyBindFunc(v, sqLsDir, L"lsdir", 2, L".s");
	xyBindFunc(v, sqIsDir, L"isdir", 2, L".s");
	xyBindFunc(v, sqFileWrite, L"fileWrite", 3, L".ss");
	xyBindFunc(v, sqFileAppend, L"fileAppend", 3, L".ss");
	xyBindFunc(v, sqFileRead, L"fileRead", 2, L".s");

	//Audio
	xyPrint(0, L"Embedding audio...");
	xyBindFunc(v, sqLoadMusic, L"loadMusic", 2, L".s");
	xyBindFunc(v, sqLoadSound, L"loadSound", 2, L".s");
	xyBindFunc(v, sqPlaySound, L"playSound", 3, L".nn");
	xyBindFunc(v, sqPlayMusic, L"playMusic", 3, L".nn");
	xyBindFunc(v, sqDeleteSound, L"deleteSound", 2, L".n");
	xyBindFunc(v, sqDeleteMusic, L"deleteMusic", 2, L".n");
	xyBindFunc(v, sqStopSound, L"stopSound", 2, L".n");
	xyBindFunc(v, sqStopMusic, L"stopMusic");
	xyBindFunc(v, sqCheckMusic, L"checkMusic");
	xyBindFunc(v, sqCheckSound, L"checkSound", 2, L".n");
	xyBindFunc(v, sqSetMaxChannels, L"setMaxChannels", 2, L".n");
	xyBindFunc(v, sqPauseMusic, L"pauseMusic");
	xyBindFunc(v, sqResumeMusic, L"resumeMusic");
	xyBindFunc(v, sqMusicPaused, L"musicPaused");

	//Shapes
	xyBindFunc(v, sqLineLine, L"hitLineLine", 9, L".nnnnnnnn");
	xyBindFunc(v, sqLineCircle, L"hitLineCircle", 8, L".nnnnnnn");
	xyBindFunc(v, sqLinePoint, L"hitLinePoint", 7, L".nnnnnn");
};

void xyUpdate() {

	//Update last button state
	for(int i = 0; i < 5; i++) {
		buttonlast[i] = buttonstate[i];
	};

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
	gvTicks = SDL_GetTicks();
	Uint32 fLength = gvTicks - gvTickLast;
	Uint32 max_delay = (1000 / gvMaxFPS);
	if (fLength < max_delay) {
		if (gvMaxFPS != 0) SDL_Delay(max_delay - fLength);
	}
	if(fLength != 0) gvFPS = 1000 / (SDL_GetTicks() - gvTickLast);
	gvTickLast = gvTicks;
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
	  xyPrint(0, L"Stack smash detected.");
};

//For converting wide chars and regular chars
wchar_t* towc(const char* s) {
	const size_t csize = strlen(s) + 1;
	wchar_t *wsarg;
	mbstowcs(wsarg, s, csize);
	return wsarg;
};

char* tostr(const wchar_t* s){
	char* csarg;
	wctomb(csarg, *s);
	return csarg;
};