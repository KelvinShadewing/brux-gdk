#include "api/main.hpp"

#include "brux/main.hpp"

#include "brux/fileio.hpp"
#include "brux/global.hpp"
#include "brux/graphics.hpp"

namespace BruxAPI {

//////////
// MAIN //
//////////

void wait(int seconds) {
	xyWait(seconds);
}

void update() {
	xyUpdate();
}

std::string getOS() {
	return SDL_GetPlatform();
}

int getTicks() {
	return SDL_GetTicks();
}

int getFPS() {
	return std::round(gvFPS);
}

void setFPS(int max_fps) {
	if (max_fps < 0) {
		throw std::runtime_error("Maximum FPS cannot be negative");
	}

	gvMaxFPS = max_fps;
}

void setWindowTitle(const std::string& title) {
	SDL_SetWindowTitle(gvWindow, title.c_str());
}

void setWindowIcon(const std::string& file) {
	if (!xyFileExists(file)) return;

	SDL_Surface* icon = IMG_Load(file.c_str());
	SDL_SetWindowIcon(gvWindow, icon);
	SDL_FreeSurface(icon);
}

int getFrames() {
	return gvFrames;
}

int displayW() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	return DM.w;
}

int displayH() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	return DM.h;
}

std::string bruxVersion() {
	return gvVNo;
}

void toggleFullScreen() {
	SDL_SetWindowFullscreen(gvWindow, (SDL_GetWindowFlags(gvWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
}

} // namespace BruxAPI
