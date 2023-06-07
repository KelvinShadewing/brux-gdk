//  Brux - Main
//  Copyright (C) 2016 KelvinShadewing
//  Copyright (C) 2023 hexaheximal
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

#include "brux/main.hpp"

#include "audio/audio.hpp"
#include "brux/core.hpp"
#include "brux/fileio.hpp"
#include "brux/global.hpp"
#include "brux/graphics.hpp"
#include "brux/input.hpp"
#include "squirrel/wrapper.hpp"

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
	int initResult = 0;
	try {
		initResult = xyInit();
	}
	catch (std::exception& err) {
		xyPrint(0, "Error initiating Brux: %s", err.what());
		xyEnd();
		return 1;
	}
	if (initResult == 0) {
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
						xygapp = curarg;
						size_t found = xygapp.find_last_of("/\\");
						gvWorkDir = xygapp.substr(0, found);
						if (chdir(gvWorkDir.c_str()) != 0) { // Check whether an error has occured
							xyPrint(0, "Error initiating Brux: Cannot change to input file working directory: %d", errno);
							xyEnd();
							return 1;
						}
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
	xyFSMount(xyGetDir(), "/", true);

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
	try {
		xyEnd();
	}
	catch (std::exception& err) {
		xyPrint(0, "Error quitting Brux: %s", err.what());
		return 1;
	}

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

	// Initialize audio
	
	xyInitAudio();

	// Get channel count

	gvMixChannels = xyGetAudioChannels();

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

	/* Bind all Brux API functions to Squirrel, using the generated wrapper. */
	xyPrint(0, "Embedding API...");
	BruxAPI::register_brux_wrapper(gvSquirrel);

	/*Error handler does not seem to print compile-time errors. I haven't
	been able to figure out why, as the same code works in my other apps,
	and is taken from the sq.c example included with Squirrel.*/
	sqstd_seterrorhandlers(gvSquirrel);

	xyPrint(0, "Squirrel initialized successfully!");

	// Initiate other
	vcTextures.push_back(0);
	vcTextureNames.push_back("");
	vcSprites.push_back(0);
	xyInitAudio();
	vcFonts.push_back(0);

	xyLoadCore(); // Squirrel-side definitions
	xyLoadActors();

	xyPrint(0, "\n================\n");

	// Return success
	
	return 1;
};

void xyEnd() {
	xyPrint(0, "\n\n================\n");

	// Cleanup all resources (except for audio)

	xyPrint(0, "Cleaning up all resources...");
	xyPrint(0, "Cleaning textures...");
	for(int i = 0; i < static_cast<int>(vcTextures.size()); i++) {
		xyDeleteImage(i);
	}

	xyPrint(0, "Cleaning sprites...");
	for(int i = 0; i < static_cast<int>(vcSprites.size()); i++) {
		delete vcSprites[i];
	}

	xyPrint(0, "Finished cleanup.");

	// Run Squirrel's garbage collector, and then close the Squirrel VM.
	
	xyPrint(0, "Closing Squirrel...");
	SQInteger garbage = sq_collectgarbage(gvSquirrel);
	xyPrint(0, "Collected %i junk obects.", garbage);
	sq_pop(gvSquirrel, 1);
	sq_close(gvSquirrel);

	// Unload all of the audio stuff

	xyPrint(0, "Unloading audio system...");
	xyUnloadAudio();

	// Close SDL

	xyPrint(0, "Closing SDL...");
	SDL_DestroyRenderer(gvRender);
	SDL_DestroyWindow(gvWindow);
	IMG_Quit();
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
	SQChar buffer[100*100] = _SC("");
	vsnprintf(buffer, sizeof(buffer), s, argv);
	va_end(argv);
	cout << buffer << endl;
	gvLog << buffer << endl;
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

	gvMouseX /= static_cast<int>(sx);
	gvMouseY /= static_cast<int>(sy);

	//Gamepad
	//Check each pad
	for(int i = 0; i < 8; i++) {
		if(SDL_NumJoysticks() > i) gvGamepad[i] = SDL_JoystickOpen(i);
	}

	//Wait for FPS limit
	//Update ticks counter for FPS
#ifdef USE_CHRONO_STEADY_CLOCK
	gvTicks = std::chrono::steady_clock::now();

	std::chrono::duration<float> fLength = gvTicks - gvTickLast;
	std::chrono::duration<float> max_delay = std::chrono::duration<float>(1.0f / gvMaxFPS);
	if (fLength < max_delay) {
		if (gvMaxFPS != 0)
			std::this_thread::sleep_for((max_delay - fLength) - std::chrono::duration<float>(0.0001f));
	}

	//Calculate time since previous tick and adjust framerate
	std::chrono::duration<float> timeSince = std::chrono::steady_clock::now() - gvTickLast;
	gvFPS = 1.0f / timeSince.count();

	// Update previous tick and increment frames
	gvTickLast = std::chrono::steady_clock::now();
#else
	gvTicks = SDL_GetTicks();
	Uint32 fLength = gvTicks - gvTickLast;
	Uint32 max_delay = (1000 / gvMaxFPS);

	if (fLength < max_delay) {
		if (gvMaxFPS != 0)
			SDL_Delay(max_delay - fLength);
	}

	if (fLength != 0) gvFPS = 1000 / static_cast<float>(SDL_GetTicks() - gvTickLast);
	gvTickLast = SDL_GetTicks();
#endif
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
