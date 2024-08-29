#include "video.hpp"

#include "brux/global.hpp"

BaseVideoAPI* gvVideoDriver = nullptr;

void xyClearScreen() {
	if (gvVideoDriver == nullptr)
		return;
	
	gvVideoDriver->clearScreen();
}

// Set draw color based on RGBA data
void xySetDrawColor(int r, int g, int b, int a) {
	if (gvVideoDriver == nullptr)
		return;

	// Set color correction
	if (r > 255) {
		r = 255;
	}

	if (r < 0) {
		r = 0;
	}

	if (g > 255) {
		g = 255;
	}

	if (g < 0) {
		g = 0;
	}

	if (b > 255) {
		b = 255;
	}

	if (b < 0) {
		b = 0;
	}

	if (a > 255) {
		a = 255;
	}

	if (a < 0) {
		a = 0;
	}

	gvVideoDriver->setDrawColor(r, g, b, a);
}

// Set draw color from 24- or 32-bit integer

void xySetDrawColor(int color) {
	if (gvVideoDriver == nullptr)
		return;

	// If the value of color is too big for a 24-bit integer, then treat it as 32-bit

	uint8_t r;
	r = ((color & 0xFF000000) >> 24);

	// Do the same for each color value

	uint8_t g;
	g = static_cast<uint8_t>((color & 0x00FF0000) >> 16);

	uint8_t b;
	b = ((color & 0x0000FF00) >> 8);

	uint8_t a;
	a = color & 0x000000FF;

	// Set the color

	gvVideoDriver->setDrawColor(r, g, b, a);

	gvDrawColor = static_cast<int>(color);

	if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
		gvDrawColor = SDL_Swap32(gvDrawColor);
	}
}


// Extract color value from a single integer

uint8_t xyGetRed(uint32_t color) {
	uint8_t r;
	r = (color & 0xFF000000) >> 24;
	return r;
}

uint8_t xyGetGreen(uint32_t color) {
	uint8_t g;
	g = (color & 0x00FF0000) >> 16;
	return g;
}

uint8_t xyGetBlue(uint32_t color) {
	uint8_t b;
	b = (color & 0x0000FF00) >> 8;
	return b;
}

uint8_t xyGetAlpha(uint32_t color) {
	uint8_t a;
	a = color & 0x000000FF;
	return a;
}

void xySetBackgroundColor(uint32_t color) {
	gvBackColor = color;
}

// Currently just a wrapper for SDL_Delay

void xyWait(int ticks) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->wait(ticks);
}

// Set draw target to a texture

void xySetDrawTarget(uint32_t tex) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->setDrawTarget(tex);
}

// Get the draw target texture

int xyGetDrawTarget() {
	if (gvVideoDriver == nullptr)
		return -1;
	return gvDrawTarget;
}

// Set draw target back to screen

void xyResetDrawTarget() {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->resetDrawTarget();
}



//////////
//IMAGES//
//////////

// Load a texture and assign it to a slot in the textures list

uint32_t xyLoadImage(const std::string& path) {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->loadImage(path);
}

uint32_t xyLoadImageKeyed(const std::string& path, uint32_t key) {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->loadImageKeyed(path, key);
}

// Draw image

void xyDrawImage(uint32_t tex, int x, int y) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawImage(tex, x, y);
}

void xyDrawImagePart(uint32_t tex, int x, int y, int ox, int oy, int w, int h) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawImagePart(tex, x, y, ox, oy, w, h);
}

void xyDrawImageEx(uint32_t tex, int x, int y, float angle, int flip, int xscale, int yscale, uint32_t color) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawImageEx(tex, x, y, angle, flip, xscale, yscale, color);
}

// Delete image

void xyDeleteImage(uint32_t tex) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->deleteImage(tex);
}

// Load a texture and assign it to a slot in the textures list

uint32_t xyNewTexture(uint32_t w, uint32_t h) {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->newTexture(w, h);
}

// Set the scale of drawing coordinates

void xySetScaling(float scale) {
	if (gvVideoDriver == nullptr || scale <= 0)
		return;

	gvVideoDriver->setScaling(scale);
}

// Set the scaling filter

void xySetScalingFilter(int hint) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->setScalingFilter(hint);
}

// Set the screen resolution

void xySetResolution(int w, int h) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->setResolution(w, h);
}

// Get the screen width

int xyScreenW() {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->screenW();
}

// Get the screen height

int xyScreenH() {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->screenH();
}

// Get the window width

int xyWindowW() {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->windowW();
}

// Get the window height

int xyWindowH() {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->windowH();
}

void xyToggleFullscreen() {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->toggleFullscreen();
}

// Set a texture's blend mode

void xyTextureSetBlendMode(int texture, int blend) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->setTextureBlendMode(texture, blend);
}

// Find a texture's ID by its name

int xyFindTexture(const std::string& name) {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->findTexture(name);
}

// Get the name of a texture

std::string xyGetTextureName(int texture) {
	if (gvVideoDriver == nullptr)
		return "";
	return gvVideoDriver->getTextureName(texture);
}

// Get a texture's filter

int xyGetTextureFilter(int tex) {
	if (gvVideoDriver == nullptr)
		return 0;
	return gvVideoDriver->getTextureFilter(tex);
}

// Set a texture's filter

void xySetTextureFilter(int tex, int filter) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->setTextureFilter(tex, filter);
}

// Print the names of all loaded textures

void xyPrintTextureNames() {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->printTextureNames();
}


/** SHAPES */

// Draw a circle

void xyDrawCircle(int x, int y, int radius, bool filled) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawCircle(x, y, radius, filled);
}

// Draw a rectangle

void xyDrawRect(int x, int y, int w, int h, bool filled) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawRect(x, y, w, h, filled);
}

// Draw a pixel

void xyDrawPoint(int x, int y) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawPoint(x, y);
}

// Draw a line

void xyDrawLine(int x1, int y1, int x2, int y2) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawLine(x1, y1, x2, y2);
}

// Draw a thick line

void xyDrawLineWide(int x1, int y1, int x2, int y2, int w) {
	if (gvVideoDriver == nullptr)
		return;
	gvVideoDriver->drawLineWide(x1, y1, x2, y2, w);
}

//////////////
// GEOMETRY //
//////////////




void xyRegisterGraphicsAPI(ssq::VM& vm) {
	vm.addFunc("clearScreen", xyClearScreen); // Doc'd
	vm.addFunc("setDrawTarget", xySetDrawTarget); // Doc'd
	vm.addFunc("getDrawTarget", xyGetDrawTarget); // Doc'd
	vm.addFunc("resetDrawTarget", xyResetDrawTarget);
	vm.addFunc("drawImage", xyDrawImage); // Doc'd
	vm.addFunc("drawImagePart", xyDrawImagePart);
	vm.addFunc("drawImageEx", xyDrawImageEx);
	vm.addFunc("setDrawColor", static_cast<void(*)(int)>(xySetDrawColor)); // Doc'd
	vm.addFunc("loadImage", xyLoadImage); // Doc'd
	vm.addFunc("loadImageKeyed", xyLoadImageKeyed); // Doc'd
	vm.addFunc("setBackgroundColor", xySetBackgroundColor); // Doc'd
	vm.addFunc("setScaling", xySetScaling);
	vm.addFunc("setScalingFilter", xySetScalingFilter); // Doc'd
	vm.addFunc("setResolution", xySetResolution); // Doc'd
	vm.addFunc("screenW", xyScreenW); // Doc'd
	vm.addFunc("screenH", xyScreenH); // Doc'd
	vm.addFunc("windowW", xyWindowW);
	vm.addFunc("windowH", xyWindowH);
	vm.addFunc("newTexture", xyNewTexture); // Doc'd
	vm.addFunc("textureSetBlendMode", xyTextureSetBlendMode); // Doc'd
	vm.addFunc("findTexture", xyFindTexture);
	vm.addFunc("deleteTexture", xyDeleteImage);
	vm.addFunc("getTextureName", xyGetTextureName);
	vm.addFunc("getTextureFilter", xyGetTextureFilter);
	vm.addFunc("setTextureFilter", xySetTextureFilter);
	vm.addFunc("printTextureNames", xyPrintTextureNames);

	/** SHAPES */
	vm.addFunc("drawCircle", xyDrawCircle); // Doc'd
	vm.addFunc("drawRec", xyDrawRect); // Clone of `drawRect()`
	vm.addFunc("drawRect", xyDrawRect); // Doc'd
	vm.addFunc("drawPoint", xyDrawPoint); // Doc'd
	vm.addFunc("drawLine", xyDrawLine); // Doc'd
	vm.addFunc("drawLineWide", xyDrawLineWide); // Doc'd
}
