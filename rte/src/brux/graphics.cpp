//  Brux - Graphics
//  Copyright (C) 2016 KelvinShadewing
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

/*===============*\
| GRAPHICS SOURCE |
\*===============*/

#include "brux/graphics.hpp"

#include <simplesquirrel/vm.hpp>

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/fileio.hpp"

//////////
//SYSTEM//
//////////

// Clear screen

void xyClearScreen() {
	SDL_RenderClear(gvRender);
}

// Set draw color based on RGBA data

void xySetDrawColor(int r, int g, int b, int a) {
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

	Uint8 _r = r, _g = g, _b = b, _a = a;

	SDL_SetRenderDrawColor(gvRender, _r, _g, _b, _a);
}

// Set draw color from 24- or 32-bit integer

void xySetDrawColor(int color) {
	// If the value of color is too big for a 24-bit integer, then treat it as 32-bit

	Uint8 r;
	r = ((color & 0xFF000000) >> 24);

	// Do the same for each color value

	Uint8 g;
	g = static_cast<Uint8>((color & 0x00FF0000) >> 16);

	Uint8 b;
	b = ((color & 0x0000FF00) >> 8);

	Uint8 a;
	a = color & 0x000000FF;

	// Set the color

	SDL_SetRenderDrawColor(gvRender, r, g, b, a);
	gvDrawColor = static_cast<int>(color);

	if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
		gvDrawColor = SDL_Swap32(gvDrawColor);
	}
}


// Extract color value from a single integer

Uint8 xyGetRed(Uint32 color) {
	Uint8 r;
	r = (color & 0xFF000000) >> 24;
	return r;
}

Uint8 xyGetGreen(Uint32 color) {
	Uint8 g;
	g = (color & 0x00FF0000) >> 16;
	return g;
}

Uint8 xyGetBlue(Uint32 color) {
	Uint8 b;
	b = (color & 0x0000FF00) >> 8;
	return b;
}

Uint8 xyGetAlpha(Uint32 color) {
	Uint8 a;
	a = color & 0x000000FF;
	return a;
}

void xySetBackgroundColor(Uint32 color) {
	gvBackColor = color;
}

// Currently just a wrapper for SDL_Delay

void xyWait(int ticks) {
	SDL_Delay(ticks);
}

// Set draw target to a texture

void xySetDrawTarget(Uint32 tex) {
	gvDrawTarget = tex;
	if (vcTextures.size() >= tex || vcTextures[tex] != 0) {
		SDL_SetRenderTarget(gvRender, vcTextures[tex]);
	}
}

// Get the draw target texture

int xyGetDrawTarget() {
	return gvDrawTarget;
}

// Set draw target back to screen

void xyResetDrawTarget() {
	SDL_SetRenderTarget(gvRender, 0);
}



//////////
//IMAGES//
//////////

// Load image

SDL_Texture* xyLoadTexture(const std::string& path) {
	SDL_Texture* newTexture = 0;

	// Load the surface
	
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	
	if (loadedSurface == NULL) {
		xyPrint("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	// Make texture from surface

	newTexture = SDL_CreateTextureFromSurface(gvRender, loadedSurface);

	if (newTexture == NULL) {
		xyPrint("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	// Delete old surface

	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

SDL_Texture* xyLoadTextureKeyed(const std::string& path, Uint32 key) {
	SDL_Texture* newTexture = NULL;

	// Load the surface

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		xyPrint("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}
	
	Uint8 r = xyGetRed(key);
	Uint8 g = xyGetGreen(key);
	Uint8 b = xyGetBlue(key);
	
	SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, r, g, b));
	
	newTexture = SDL_CreateTextureFromSurface(gvRender, loadedSurface);
	
	if (newTexture == NULL) {
		xyPrint("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

// Load a texture and assign it to a slot in the textures list

Uint32 xyLoadImage(const std::string& path) {
	SDL_Texture* nimg = xyLoadTexture(path.c_str());

	if (!nimg) {
		xyPrint("Unable to load file: %s", path.c_str());
		gvQuit = 1;
	}

	// Make sure vcTextures[0] == 0

	if (vcTextures.size() == 1) {
		vcTextures.push_back(0);
	}

	// Add texture name

	while (vcTextureNames.size() == 1) {
		vcTextureNames.push_back("");
	}

	std::string name = path;
	std::string::size_type slashnum = path.find_last_of("/");
	
	if (slashnum != std::string::npos) {
		name = path.substr(slashnum + 1, name.length() - 1);
	}

	for (Uint32 i = 1; i < vcTextureNames.size(); i++) {
		if (vcTextureNames[i] == "") {
			vcTextureNames[i] = name;
			vcTextures[i] = nimg;
			return i;
		}
	}

	// Return the texture index
	
	vcTextureNames.push_back(name);
	vcTextures.push_back(nimg);

	return vcTextures.size() - 1;
}

Uint32 xyLoadImageKeyed(const std::string& path, Uint32 key) {
	SDL_Texture* nimg = xyLoadTextureKeyed(path, key);

	if (!nimg) {
		xyPrint("Unable to load file: %s", path.c_str());
		gvQuit = 1;
	}

	// Make sure vcTextures[0] == 0

	if (vcTextures.size() == 1) {
		vcTextures.push_back(0);
	}

	// Add texture name

	while (vcTextureNames.size() == 1) {
		vcTextureNames.push_back("");
	}

	std::string name = path;
	std::string::size_type slashnum = path.find_last_of("/");

	if (slashnum != std::string::npos) {
		name = path.substr(slashnum + 1, name.length() - 1);
	}

	for (Uint32 i = 1; i < vcTextureNames.size(); i++) {
		if (vcTextureNames[i] == "") {
			vcTextureNames[i] = name;
			vcTextures[i] = nimg;
			return i;
		}
	}

	// Return the texture index

	vcTextureNames.push_back(name);
	vcTextures.push_back(nimg);
	
	return vcTextures.size() - 1;
}

// Draw image

void xyDrawImage(Uint32 tex, int x, int y) {
	SDL_Rect rec;
	
	rec.x = x;
	rec.y = y;

	// Make sure that the texture index is valid

	if (tex >= vcTextures.size()) {
		return;
	}

	// Make sure that the texture exists

	if (vcTextures[tex] == NULL) {
		return;
	}

	SDL_QueryTexture(vcTextures[tex], 0, 0, &rec.w, &rec.h);
	SDL_RenderCopy(gvRender, vcTextures[tex], 0, &rec);
}

void xyDrawImagePart(Uint32 tex, int x, int y, int ox, int oy, int w, int h) {
	SDL_Rect rec;

	rec.x = x;
	rec.y = y;
	rec.w = w;
	rec.h = h;

	SDL_Rect slice;

	slice.x = ox;
	slice.y = oy;
	slice.w = w;
	slice.h = h;

	// Make sure that the texture index is valid

	if (tex >= vcTextures.size()) {
		return;
	}

	// Make sure that the texture exists

	if (vcTextures[tex] == NULL) {
		return;
	}

	SDL_RenderCopy(gvRender, vcTextures[tex], &slice, &rec);
}

void xyDrawImageEx(Uint32 tex, int x, int y, float angle, int flip, int xscale, int yscale, Uint32 color) {
	SDL_Rect rec;

	rec.x = 0;
	rec.y = 0;

	SDL_Rect des;

	des.x = x;
	des.y = y;

	// Break color into 8-bit versions

	Uint8 r, g, b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;

	SDL_Point *piv = new SDL_Point;

	piv->x = 0;
	piv->y = 0;

	// Make sure that the texture index is valid

	if (tex >= vcTextures.size()) {
		return;
	}

	// Make sure that the texture exists

	if (vcTextures[tex] == NULL) {
		return;
	}

	SDL_QueryTexture(vcTextures[tex], 0, 0, &rec.w, &rec.h);
	
	des.w = rec.w * xscale;
	des.h = rec.h * yscale;
	
	SDL_SetTextureColorMod(vcTextures[tex], r, g, b);
	SDL_RenderCopyEx(gvRender, vcTextures[tex], &rec, &des, (double)angle, piv, static_cast<SDL_RendererFlip>(flip));
	SDL_SetTextureColorMod(vcTextures[tex], 255, 255, 255);
}

// Delete image

void xyDeleteImage(Uint32 tex) {
	if (tex >= vcTextures.size()) {
		return;
	}

	SDL_DestroyTexture(vcTextures[tex]);

	if (tex < vcTextures.size() - 1) {
		vcTextures[tex] = 0;
		vcTextureNames[tex] = "";
		return;
	}

	vcTextures.pop_back();
	vcTextureNames.pop_back();
}

// Load a texture and assign it to a slot in the textures list

Uint32 xyNewTexture(Uint32 w, Uint32 h) {
	SDL_Texture* nimg = SDL_CreateTexture(gvRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

	if (!nimg) {
		xyPrint("Unable to create texture!");
		gvQuit = 1;
	}

	// Make sure vcTextures[0] == 0

	if (vcTextures.size() == 1) {
		vcTextures.push_back(0);
	}

	// Add texture name
	
	while (vcTextureNames.size() == 1) {
		vcTextureNames.push_back("");
	}

	for (Uint32 i = 1; i < vcTextureNames.size(); i++) {
		if (vcTextureNames[i] == "") {
			vcTextureNames[i] = "new-texture-" + std::to_string(i);
			vcTextures[i] = nimg;
			return i;
		}
	}

	// Return the texture index

	vcTextureNames.push_back("new-texture-" + std::to_string(vcTextures.size()));
	vcTextures.push_back(nimg);

	return vcTextures.size() - 1;
}

// Set the scale of drawing coordinates

void xySetScaling(float scale) {
	if (scale <= 0) {
		return;
	}

	SDL_RenderSetScale(gvRender, scale, scale);
}

// Set the scaling filter

void xySetScalingFilter(int hint) {
	if (hint > 2) {
		hint = 2;
	}
	else if (hint < 0) {
		hint = 0;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(hint).c_str());
}

// Set the screen resolution

void xySetResolution(int w, int h) {
	// Don't allow the width and/or height to be 0
	if (w < 1 || h < 1) {
		throw std::runtime_error("Window dimensions cannot be 0");
	}

	SDL_Rect screensize;

	screensize.x = 0;
	screensize.y = 0;
	screensize.w = w;
	screensize.h = h;

	SDL_RenderSetViewport(gvRender, &screensize);
	SDL_RenderSetLogicalSize(gvRender, w, h);
	SDL_SetWindowSize(gvWindow, w, h);
	SDL_SetWindowMinimumSize(gvWindow, w, h);
}

// Get the screen width

int xyScreenW() {
	SDL_Rect vp;

	SDL_RenderGetViewport(gvRender, &vp);

	return vp.w;
}

// Get the screen height

int xyScreenH() {
	SDL_Rect vp;

	SDL_RenderGetViewport(gvRender, &vp);

	return vp.h;
}

// Get the window width

int xyWindowW() {
	int w;

	SDL_GetWindowSize(gvWindow, &w, 0);

	return w;
}

// Get the window height

int xyWindowH() {
	int h;

	SDL_GetWindowSize(gvWindow, 0, &h);

	return h;
}

// Set a texture's blend mode

void xyTextureSetBlendMode(int texture, int blend) {
	if (texture < 0 || texture > static_cast<int>(vcTextures.size()) - 1) {
		throw std::runtime_error("Invalid texture ID. Cannot set blend mode");
	}

	SDL_BlendMode mode;

	switch (blend) {
		case 0:
			mode = SDL_BLENDMODE_NONE;
			break;
		case 1:
			mode = SDL_BLENDMODE_BLEND;
			break;
		case 2:
			mode = SDL_BLENDMODE_ADD;
			break;
		case 3:
			mode = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT, SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT);
			break;
		case 4:
			mode = SDL_BLENDMODE_MOD;
			break;
		default:
			mode = SDL_BLENDMODE_NONE;
			break;
	}

	SDL_SetTextureBlendMode(vcTextures[texture], mode);
}

// Find a texture's ID by its name

int xyFindTexture(const std::string& name) {
	for (int i = 0; i < vcTextureNames.size(); i++) {
		if (vcTextureNames[i] == name) {
			return i;
		}
	}

	return 0;
}

// Get the name of a texture

std::string xyGetTextureName(int texture) {
	if (texture > 0 && texture < vcTextureNames.size()) {
		return vcTextureNames[texture];
	}

	return "";
}

// Get a texture's filter

int xyGetTextureFilter(int tex) {
	SDL_ScaleMode sm = (SDL_ScaleMode)0;

	if(tex > 0 && tex < vcTextures.size() && vcTextures[tex] != 0)
		SDL_GetTextureScaleMode(vcTextures[tex], &sm);
	else
		xyPrint("WARNING: Texture not found!");

	return (int)sm;
}

// Set a texture's filter

void xySetTextureFilter(int tex, int filter) {
	SDL_ScaleMode sm = (SDL_ScaleMode)std::min(std::max(filter, 0), 2);

	if(tex > 0 && tex < vcTextures.size() && vcTextures[tex] != 0)
		SDL_SetTextureScaleMode(vcTextures[tex], sm);
	else
		xyPrint("WARNING: Texture not found!");
}

// Print the names of all loaded textures

void xyPrintTextureNames() {
	for (int i = 0; i < vcTextureNames.size(); i++) {
		xyPrint("%d - %s", i, vcTextureNames[i].c_str());
	}
}


/** SHAPES */

// Draw a circle

void xyDrawCircle(int x, int y, int radius, bool filled) {
	if (filled)
		filledCircleColor(gvRender, x, y, radius, gvDrawColor);
	else
		circleColor(gvRender, x, y, radius, gvDrawColor);
}

// Draw a rectangle

void xyDrawRect(int x, int y, int w, int h, bool filled) {
	if (filled)
		boxColor(gvRender, x, y, x + w, y + h, gvDrawColor);
	else
		rectangleColor(gvRender, x, y, x + w, y + h, gvDrawColor);
}

// Draw a pixel

void xyDrawPoint(int x, int y) {
	pixelColor(gvRender, x, y, gvDrawColor);
}

// Draw a line

void xyDrawLine(int x1, int y1, int x2, int y2) {
	thickLineColor(gvRender, x1, y1, x2, y2, 1, gvDrawColor);
}

// Draw a thick line

void xyDrawLineWide(int x1, int y1, int x2, int y2, int w) {
	thickLineColor(gvRender, x1, y1, x2, y2, w, gvDrawColor);
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
