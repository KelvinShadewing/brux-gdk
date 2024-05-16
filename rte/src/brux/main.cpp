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

#include <simplesquirrel/simplesquirrel.hpp>

#include "audio/audio.hpp"
#include "brux/core.hpp"
#include "brux/fileio.hpp"
#include "brux/global.hpp"
#include "brux/graphics.hpp"
#include "brux/input.hpp"
#include "brux/maths.hpp"
#include "brux/shapes.hpp"
#include "brux/sprite.hpp"
#include "brux/text.hpp"

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
	// Process arguments

	std::string xygapp = "";
	std::string curarg = "";
	
	for (int i = 1; i < argc; i++) {
		curarg = argv[i];

		// Handle arguments
		
		if (curarg == "-f" || curarg == "--fullscreen") {
			SDL_SetWindowFullscreen(gvWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		
		// Check if the argument is long enough to be a source file
		
		if (curarg.length() > 4) {
			// Check if the argument is a source file
			
			if (curarg.substr(curarg.find_last_of('.')) == ".sq" || curarg.substr(curarg.find_last_of('.')) == ".nut" || curarg.substr(curarg.find_last_of('.')) == ".brx") {
				// Check if the file actually exists

				if (xyLegacyFileExists(curarg)) {
					// If everything looks good, set it as the main file.
					
					xygapp = curarg;
					
					size_t found = xygapp.find_last_of("/\\");
					
					//If local file provided without ./ before it, use local directory
					if (found != -1) {
						gvWorkDir = xygapp.substr(0, found);

						// Remove dir from xygapp so we can actually find the file
						xygapp = xygapp.substr(found+1);
						
						if (chdir(gvWorkDir.c_str()) != 0) {
							xyPrint("Error initializing Brux: Cannot change to input file working directory: %d", errno);
							xyPrint(gvWorkDir.c_str());
							xyEnd();
							return 1;
						}
					} else {
						gvWorkDir = ".";
					}
					
					const std::string curdir = xyGetDir();
					
					xyPrint("Working directory: %s", curdir.c_str());
				}
			}
		}
	}

	// Initialize the file system (PhysFS)
	xyFSInit();

	// Mount the current working directory.
	xyFSMount(xyGetDir(), "/", true);

	// Set the current write directory to a default for Brux.
	// Can be changed later by the game.
	xySetWriteDir(xyGetPrefDir("brux", "brux"));

	bool shouldLoad = false;
	
	if (xygapp != "") {
		// If xygapp is not a blank string at this point, we can safely assume that it exists.
		
		shouldLoad = true;
	} else {
		// If the filename is blank, attempt to load game.brx or test.nut as a fallback.
		if (xyFileExists("game.brx")) {
			xygapp = "game.brx";
			shouldLoad = true;
		} else if (xyFileExists("test.nut")) {
			xygapp = "test.nut";
			shouldLoad = true;
		}
	}
	
	// Handle situations where a main file can't be found
	
	// if (!shouldLoad) {
	// 	puts("ERROR: Unable to load the main file. Make sure that it exists.");
	// 	return 1;
	// }
	
	// Initialize everything
	
	int initResult = 0;
		
	try {
		initResult = xyInit();
	} catch (std::exception& err) {
		xyPrint("Error initializing Brux: %s", err.what());
		xyPrint(gvWorkDir.c_str());
		xyEnd();
		return 1;
	}
		
	if (initResult == 0) {
		xyPrint("Failed to initiate Brux!");
		xyEnd();
		return 1;
	}
		
	SDL_ShowCursor(0);
	
	try {
		xyDonut(xygapp);
	}
	catch (const std::exception& err) {
		xyPrint("Error running '%s': %s", xygapp.c_str(), err.what());
	}
	
	// Unload everything once the squirrel code is finished running
	
	try {
		xyEnd();
	} catch (std::exception& err) {
		xyPrint("Error quitting Brux: %s", err.what());
		return 1;
	}

	return 0;
}

///////////////////
//OTHER FUNCTIONS//
///////////////////

// Handles initialization of SDL2 and Squirrel

int xyInit() {
	// Initiate log file

	remove("log.txt");
	gvLog.open("log.txt", std::ios_base::out);

	// Print opening message
	
	xyPrint("\n/========================\\\n| BRUX GAME RUNTIME LOG |\n\\========================/\n\n");

	// Initiate SDL2

	SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
#ifdef __EMSCRIPTEN__
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
#else
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
#endif
		xyPrint("Failed to initialize! %s", SDL_GetError());
		return 0;
	}

	// Create window
	
	gvWindow = SDL_CreateWindow("Brux GDK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gvScrW, gvScrH, SDL_WINDOW_RESIZABLE);

	if (gvWindow == 0) {
		xyPrint("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return 0;
	} else {
		// Create renderer for window

		gvRender = SDL_CreateRenderer(gvWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gvRender == 0) {
			xyPrint("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return 0;
		} else {
			// Initialize renderer color

			SDL_SetRenderDrawColor(gvRender, 0xFF, 0xFF, 0xFF, 0xFF);

			// Initialize PNG loading

			if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				xyPrint("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return 0;
			}

			// Set up the viewport

			SDL_Rect screensize;
			screensize.x = 0;
			screensize.y = 0;
			screensize.w = gvScrW;
			screensize.h = gvScrH;
			SDL_RenderSetViewport(gvRender, &screensize);
			SDL_RenderSetLogicalSize(gvRender, gvScrW, gvScrH);

			// Set the mimumum window size
			// No idea why it didn't do this before.

			SDL_SetWindowMinimumSize(gvWindow, gvScrW, gvScrH);
		}
	}

	// Initialize audio

	xyInitAudio();

	// Get channel count

	gvMixChannels = xyGetAudioChannels();

	// Initialize input

	xyInitInput();

	xyPrint("SDL initialized successfully!");

	// Initiate Squirrel

	gvSquirrel = ssq::VM(1024, ssq::Libs::IO | ssq::Libs::SYSTEM | ssq::Libs::MATH | ssq::Libs::STRING);

	gvSquirrel.setPrintFunc(sqPrint, sqError);

	// Bind all Brux API functions to Squirrel

	xyPrint("Embedding API...");
	xyRegisterAudioAPI(gvSquirrel);
	xyRegisterCoreAPI(gvSquirrel);
	xyRegisterFileIOAPI(gvSquirrel);
	xyRegisterGraphicsAPI(gvSquirrel);
	xyRegisterInputAPI(gvSquirrel);
	xyRegisterMainAPI(gvSquirrel);
	xyRegisterMathsAPI(gvSquirrel);
	xyRegisterShapesAPI(gvSquirrel);
	xyRegisterSpriteAPI(gvSquirrel);
	xyRegisterTextAPI(gvSquirrel);

	// The error handler does not seem to print compile-time errors.
	// I haven't been able to figure out why, as the same code works in my other apps,
	// and is taken from the sq.c example included with Squirrel.
	gvSquirrel.setStdErrorFunc();

	xyPrint("Squirrel initialized successfully!");

	// Initiate other things

	vcTextures.push_back(0);
	vcTextureNames.push_back("");
	vcSprites.push_back(0);
	xyInitAudio();
	vcFonts.push_back(0);

	// Squirrel-side definitions

	xyLoadCore();
	xyLoadActors();

	xyPrint("\n================\n");

	// Return success

	return 1;
}

void xyEnd() {
	xyPrint("\n\n================\n");

	// Cleanup all resources (except for audio)

	xyPrint("Cleaning up all resources...");
	xyPrint("Cleaning textures...");

	for (int i = 0; i < vcTextures.size(); i++) {
		xyDeleteImage(i);
	}

	xyPrint("Cleaning sprites...");
	
	for (int i = 0; i < vcSprites.size(); i++) {
		delete vcSprites[i];
	}

	xyPrint("Finished cleanup.");

	// Run Squirrel's garbage collector, and then close the Squirrel VM.
	
	xyPrint("Closing Squirrel...");
	SQInteger garbage = sq_collectgarbage(gvSquirrel.getHandle());
	xyPrint("Collected %i junk obects.", garbage);
	gvSquirrel.destroy();

	// Unload all of the audio stuff

	xyPrint("Unloading audio system...");
	xyUnloadAudio();

	// Close SDL

	xyPrint("Closing SDL...");
	SDL_DestroyRenderer(gvRender);
	SDL_DestroyWindow(gvWindow);
	IMG_Quit();
	SDL_Quit();

	// Destroy the file system (PhysFS)

	xyPrint("Closing file system...");
	xyFSDeinit();

	// Close log file

	xyPrint("System closed successfully!");
	gvLog.close();
}

void xyPrint(const SQChar *s, ...) {
	va_list argv;
	va_start(argv, s);

	SQChar buffer[100*100] = _SC("");

	vsnprintf(buffer, sizeof(buffer), s, argv);
	va_end(argv);

	std::cout << buffer << std::endl;
	gvLog << buffer << std::endl;
}

void sqPrint(HSQUIRRELVM v, const SQChar *s, ...) {
	va_list argv;
	va_start(argv, s);

	SQChar buffer[100*100] = _SC("");

	vsnprintf(buffer, sizeof(buffer), s, argv);
	va_end(argv);

	std::cout << buffer << std::endl;
	gvLog << buffer << std::endl;
}

void sqError(HSQUIRRELVM v, const SQChar *s, ...) {
	gvDidError = true;

	va_list argv;
	va_start(argv, s);

	SQChar buffer[100*100] = _SC("");

	vsnprintf(buffer, sizeof(buffer), s, argv);
	va_end(argv);

	std::cout << buffer << std::endl;
	gvLog << buffer << std::endl;
}

void xyUpdate() {
	if (!gvUpdateDeprecationWarningShown) {
		xyPrint("WARNING: update() is deprecated and will be removed in a future release.");
		gvUpdateDeprecationWarningShown = true;
	}

	// Update last button state

	int i;

	for (i = 0; i < 5; i++) {
		buttonlast[i] = buttonstate[i];
	}

	// Reset the mouse wheel position

	mouseWheelX = 0;
	mouseWheelY = 0;

	// Reset event-related globals

	gvQuit = 0;

	// Poll events

	SDL_Event Event;

	while (SDL_PollEvent(&Event)) {
		// Quit if SDL tells us to

		if(Event.type == SDL_QUIT) {
			gvQuit = 1;
			continue;
		}

		// Handle mouse button press/release
		// Significantly code-golfed by hexaheximal

		if (Event.type == SDL_MOUSEBUTTONDOWN || Event.type == SDL_MOUSEBUTTONUP) {
			// The new state will be 1 if it's down, or 0 if it's up.

			int newButtonState = Event.type == SDL_MOUSEBUTTONDOWN ? 1 : 0;

			switch (Event.button.button) {
				case SDL_BUTTON_LEFT:
					buttonstate[0] = newButtonState;
					break;
				case SDL_BUTTON_MIDDLE:
					buttonstate[1] = newButtonState;
					break;
				case SDL_BUTTON_RIGHT:
					buttonstate[2] = newButtonState;
					break;
				case SDL_BUTTON_X1:
					buttonstate[3] = newButtonState;
					break;
				case SDL_BUTTON_X2:
					buttonstate[4] = newButtonState;
					break;
				default:
					xyPrint("Unknown button pressed! This should never happen!");
					break;
			}

			continue;
		}

		// Handle mouse wheel movement

		if (Event.type == SDL_MOUSEWHEEL) {
			mouseWheelX = Event.wheel.x;
			mouseWheelY = Event.wheel.y;
			continue;
		}

		// Handle text input

		if (Event.type == SDL_TEXTINPUT) {
			gvInputString = Event.text.text;
			continue;
		}
	}

	// Update the game window

	SDL_RenderPresent(gvRender);

	Uint32 olddraw = gvDrawColor;

	xySetDrawColor(gvBackColor);

	SDL_RenderClear(gvRender);

	xySetDrawColor(olddraw);

	if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
		gvDrawColor = SDL_Swap32(gvDrawColor);
	}

	// Update input

	keylast = keystate;
	SDL_PumpEvents();

	for (int i = 0; i < 322; i++) {
		keystate[i] = sdlKeys[i];
	}

	SDL_GetMouseState(&gvMouseX, &gvMouseY);

	// This algorithm is a complicated mess
	// TODO: clean this up later

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 32; j++) {
			gvPadLastButton[i][j] = gvPadButton[i][j];
		}

		if (SDL_JoystickGetAttached(gvGamepad[i])) {
			gvPadHatLast[i] = gvPadHat[i];
			gvPadHat[i] = SDL_JoystickGetHat(gvGamepad[i], 0);

			for (int j = 0; j < 10; j++) {
				gvPadLastAxis[i][j] = gvPadAxis[i][j];
				gvPadAxis[i][j] = SDL_JoystickGetAxis(gvGamepad[i], j);
			}

			for (int j = 0; j < 32; j++) {
				gvPadLastButton[i][j] = gvPadButton[i][j];
				gvPadButton[i][j] = SDL_JoystickGetButton(gvGamepad[i], j);
			}

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

			for (int j = 0; j < 10; j++) {
				gvPadAxis[i][j] = 0;
			}

			for (int j = 0; j < 32; j++) {
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

	// Divide by scale

	float sx, sy;

	SDL_RenderGetScale(gvRender, &sx, &sy);

	// This code was originally broken in a way that could cause a crash because it didn't properly handle floating-point numbers.
	// Should be fixed now.

	if (1.0 > sx) {
		sx = 1.0;
	}

	if (1.0 > sy) {
		sy = 1.0;
	}

	gvMouseX /= static_cast<int>(sx);
	gvMouseY /= static_cast<int>(sy);

	// Gamepad
	// Check each gamepad and keep track of which ones exist
	
	for (int i = 0; i < 8; i++) {
		if (SDL_NumJoysticks() > i) { 
			gvGamepad[i] = SDL_JoystickOpen(i);
		}
	}

	// Wait for FPS limit
	// Update ticks counter for FPS

#ifdef USE_CHRONO_STEADY_CLOCK
	gvTicks = std::chrono::steady_clock::now();

	std::chrono::duration<float> fLength = gvTicks - gvTickLast;
	std::chrono::duration<float> max_delay = std::chrono::duration<float>(1.0f / gvMaxFPS);
	if (fLength < max_delay) {
		if (gvMaxFPS != 0)
			std::this_thread::sleep_for((max_delay - fLength) - std::chrono::duration<float>(0.0001f));
	}

	// Calculate time since previous tick and adjust framerate

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
}

int xyGetFPS() {
	return static_cast<int>(std::round(gvFPS));
}

void xySetFPS(int max_fps) {
	if (max_fps < 0) {
		throw std::runtime_error("Maximum FPS cannot be negative");
	}

	gvMaxFPS = max_fps;
}

void xySetWindowTitle(const std::string& title) {
	SDL_SetWindowTitle(gvWindow, title.c_str());
}

void xySetWindowIcon(const std::string& file) {
	if (!xyFileExists(file)) {
		return;
	}

	SDL_Surface* icon = IMG_Load(file.c_str());
	SDL_SetWindowIcon(gvWindow, icon);
	SDL_FreeSurface(icon);
}

int xyGetFrames() {
	return gvFrames;
}

int xyDisplayW() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	return DM.w;
}

int xyDisplayH() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	return DM.h;
}

std::string xyBruxVersion() {
	return gvVNo;
}

void xyToggleFullscreen() {
	SDL_SetWindowFullscreen(gvWindow, (SDL_GetWindowFlags(gvWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
}

int xyGetOS() {
#ifdef _WIN32
	return OS_WINDOWS;
#endif
#ifdef __gnu_linux__
	return OS_LINUX;
#endif
#ifdef __ANDROID__
	return OS_ANDROID;
#endif
#ifdef __APPLE__
	return OS_MAC;
#endif
#ifdef _DINGUX
	return OS_DINGUX;
#endif
}

void __stack_chk_fail(void) {
	xyPrint("Stack smash detected.");
}


void xyRegisterMainAPI(ssq::VM& vm) {
	vm.addFunc("wait", xyWait); // Doc'd
	vm.addFunc("update", xyUpdate); // Doc'd
	vm.addFunc("getOS", xyGetOS); // Doc'd
	vm.addFunc("getTicks", SDL_GetTicks); // Doc'd
	vm.addFunc("getFPS", xyGetFPS); // Doc'd
	vm.addFunc("setFPS", xySetFPS); // Doc'd
	vm.addFunc("setWindowTitle", xySetWindowTitle); // Doc'd
	vm.addFunc("setWindowIcon", xySetWindowIcon); // Doc'd
	vm.addFunc("getFrames", xyGetFrames); // Doc'd
	vm.addFunc("displayW", xyDisplayW); // Doc'd
	vm.addFunc("displayH", xyDisplayH); // Doc'd
	vm.addFunc("bruxVersion", xyBruxVersion); // Doc'd
	vm.addFunc("toggleFullscreen", xyToggleFullscreen); // Doc'd
}
