#include "video_sdl2.hpp"
#include "brux/global.hpp"

void SDL2VideoBackend::wait(int ticks) {
	SDL_Delay(ticks);
}

void SDL2VideoBackend::clearScreen() {
	SDL_RenderClear(mRenderer);
}

void SDL2VideoBackend::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
}

int SDL2VideoBackend::getDrawTarget() {
	return gvDrawTarget;
}

void SDL2VideoBackend::setDrawTarget(Uint32 tex) {
	gvDrawTarget = tex;

	if (vcTextures.size() >= tex || vcTextures[tex] != 0) {
		SDL_SetRenderTarget(gvRender, vcTextures[tex]);
	}
}

void SDL2VideoBackend::resetDrawTarget() {
	SDL_SetRenderTarget(mRenderer, NULL);
}

void SDL2VideoBackend::drawImage(Uint32 tex, int x, int y) {
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

void SDL2VideoBackend::drawImagePart(Uint32 tex, int x, int y, int ox, int oy, int w, int h) {
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

void SDL2VideoBackend::drawImageEx(Uint32 tex, int x, int y, float angle, int flip, int xscale, int yscale, Uint32 color) {
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

SDL_Texture* SDL2VideoBackend::loadTexture(const std::string& path) {
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

SDL_Texture* SDL2VideoBackend::loadTextureKeyed(const std::string& path, Uint32 key) {
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

Uint32 SDL2VideoBackend::loadImage(const std::string& path) {
	SDL_Texture* nimg = loadTexture(path.c_str());

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

Uint32 SDL2VideoBackend::loadImageKeyed(const std::string& path, Uint32 key) {
	SDL_Texture* nimg = loadTextureKeyed(path, key);

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

void SDL2VideoBackend::deleteImage(Uint32 img) {
	if (img >= vcTextures.size()) {
		return;
	}

	SDL_DestroyTexture(vcTextures[img]);

	if (img < vcTextures.size() - 1) {
		vcTextures[img] = 0;
		vcTextureNames[img] = "";
		return;
	}

	vcTextures.pop_back();
	vcTextureNames.pop_back();
}

Uint32 SDL2VideoBackend::newTexture(Uint32 w, Uint32 h) {
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

void SDL2VideoBackend::setScaling(float scale) {
	SDL_RenderSetScale(gvRender, scale, scale);
}

void SDL2VideoBackend::setScalingFilter(int hint) {
	if (hint > 2) {
		hint = 2;
	} else if (hint < 0) {
		hint = 0;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(hint).c_str());
}

void SDL2VideoBackend::setResolution(int w, int h) {
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

int SDL2VideoBackend::screenW() {
	SDL_Rect vp;

	SDL_RenderGetViewport(gvRender, &vp);

	return vp.w;
}

int SDL2VideoBackend::screenH() {
	SDL_Rect vp;

	SDL_RenderGetViewport(gvRender, &vp);

	return vp.h;
}

int SDL2VideoBackend::windowW() {
	int w;

	SDL_GetWindowSize(gvWindow, &w, 0);

	return w;
}

int SDL2VideoBackend::windowH() {
	int h;

	SDL_GetWindowSize(gvWindow, 0, &h);

	return h;
}

int SDL2VideoBackend::getTextureFilter(int tex) {
	SDL_ScaleMode sm = (SDL_ScaleMode)0;

	if(tex > 0 && tex < vcTextures.size() && vcTextures[tex] != 0)
		SDL_GetTextureScaleMode(vcTextures[tex], &sm);
	else
		xyPrint("WARNING: Texture not found!");

	return (int)sm;
}

void SDL2VideoBackend::setTextureFilter(int tex, int filter) {
	SDL_ScaleMode sm = (SDL_ScaleMode)std::min(std::max(filter, 0), 2);

	if(tex > 0 && tex < vcTextures.size() && vcTextures[tex] != 0)
		SDL_SetTextureScaleMode(vcTextures[tex], sm);
	else
		xyPrint("WARNING: Texture not found!");
}

void SDL2VideoBackend::setTextureBlendMode(int texture, int blend) {
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

std::string SDL2VideoBackend::getTextureName(int texture) {
	if (texture > 0 && texture < vcTextureNames.size()) {
		return vcTextureNames[texture];
	}

	return "";
}

int SDL2VideoBackend::findTexture(const std::string& name) {
	for (int i = 0; i < vcTextureNames.size(); i++) {
		if (vcTextureNames[i] == name) {
			return i;
		}
	}

	return 0;
}

void SDL2VideoBackend::printTextureNames() {
	for (int i = 0; i < vcTextureNames.size(); i++) {
		xyPrint("%d - %s", i, vcTextureNames[i].c_str());
	}
}

/** SHAPES */
void SDL2VideoBackend::drawRect(int x, int y, int w, int h, bool filled) {
	if (filled)
		boxColor(gvRender, x, y, x + w, y + h, gvDrawColor);
	else
		rectangleColor(gvRender, x, y, x + w, y + h, gvDrawColor);
}

// Draw a pixel

void SDL2VideoBackend::drawPoint(int x, int y) {
	pixelColor(gvRender, x, y, gvDrawColor);
}

// Draw a line

void SDL2VideoBackend::drawLine(int x1, int y1, int x2, int y2) {
	thickLineColor(gvRender, x1, y1, x2, y2, 1, gvDrawColor);
}

// Draw a thick line

void SDL2VideoBackend::drawLineWide(int x1, int y1, int x2, int y2, int w) {
	thickLineColor(gvRender, x1, y1, x2, y2, w, gvDrawColor);
}
