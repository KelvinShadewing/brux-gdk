#include "video_sdl2.hpp"
#include "brux/global.hpp"

std::string getSDLVer() {
	SDL_version ver;

	SDL_GetVersion(&ver);	

	return (char)ver.major + (std::string)"." + (char)ver.minor + (std::string) + "." + (char)ver.patch;
}

SDL2VideoBackend::SDL2VideoBackend() : BaseVideoAPI("SDL2", getSDLVer()) {
	mWindow = SDL_CreateWindow("Brux", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gvScrW, gvScrH, SDL_WINDOW_RESIZABLE);

	if (mWindow == 0) {
		xyPrint("Window could not be created! SDL Error: %s\n", SDL_GetError());
		throw std::runtime_error("SDL2 Window Creation Error");
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	if (mRenderer == 0) {
		xyPrint("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		throw std::runtime_error("SDL2 Renderer Creation Error");
	}

	setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);

	// Initialize PNG loading
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		xyPrint("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

		throw std::runtime_error("SDL_image init error");
	}

	// Set up the viewport

	SDL_Rect screensize;
	screensize.x = 0;
	screensize.y = 0;
	screensize.w = gvScrW;
	screensize.h = gvScrH;
	SDL_RenderSetViewport(mRenderer, &screensize);
	SDL_RenderSetLogicalSize(mRenderer, gvScrW, gvScrH);

	// Set the mimumum window size
	// No idea why it didn't do this before.

	SDL_SetWindowMinimumSize(mWindow, gvScrW, gvScrH);

	mTextures.push_back(0);
	mTextureNames.push_back("");
}

SDL2VideoBackend::~SDL2VideoBackend() {
	for (int i = 0; i < mTextures.size(); i++) {
		if (mTextures[i] != 0) deleteImage(i);
	}

	IMG_Quit();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindowSurface(mWindow);
}

void SDL2VideoBackend::setTitle(const std::string& title) {
	SDL_SetWindowTitle(mWindow, title.c_str());
}

void SDL2VideoBackend::setIcon(const std::string& path) {
	SDL_Surface* icon = IMG_Load(path.c_str());
	SDL_SetWindowIcon(mWindow, icon);
	SDL_FreeSurface(icon);
}

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

	if (mTextures.size() >= tex || mTextures[tex] != 0) {
		SDL_SetRenderTarget(mRenderer, mTextures[tex]);
	}
}

void SDL2VideoBackend::resetDrawTarget() {
	SDL_SetRenderTarget(mRenderer, NULL);
}

int SDL2VideoBackend::textureCount() {
	return mTextures.size();
}

void SDL2VideoBackend::drawImage(Uint32 tex, int x, int y) {
	SDL_Rect rec;
	
	rec.x = x;
	rec.y = y;

	// Make sure that the texture index is valid

	if (tex >= mTextures.size()) {
		return;
	}

	// Make sure that the texture exists

	if (mTextures[tex] == NULL) {
		return;
	}

	SDL_QueryTexture(mTextures[tex], 0, 0, &rec.w, &rec.h);
	SDL_RenderCopy(mRenderer, mTextures[tex], 0, &rec);
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

	if (tex >= mTextures.size()) {
		return;
	}

	// Make sure that the texture exists

	if (mTextures[tex] == NULL) {
		return;
	}

	SDL_RenderCopy(mRenderer, mTextures[tex], &slice, &rec);
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

	if (tex >= mTextures.size()) {
		return;
	}

	// Make sure that the texture exists

	if (mTextures[tex] == NULL) {
		return;
	}

	SDL_QueryTexture(mTextures[tex], 0, 0, &rec.w, &rec.h);
	
	des.w = rec.w * xscale;
	des.h = rec.h * yscale;
	
	SDL_SetTextureColorMod(mTextures[tex], r, g, b);
	SDL_RenderCopyEx(mRenderer, mTextures[tex], &rec, &des, (double)angle, piv, static_cast<SDL_RendererFlip>(flip));
	SDL_SetTextureColorMod(mTextures[tex], 255, 255, 255);
}

void SDL2VideoBackend::renderCopy(int tex, SDL_Rect* rec, SDL_Rect* des) {
	if (tex < 0 || tex > static_cast<int>(mTextures.size()) - 1)
		return;

	SDL_RenderCopy(mRenderer, mTextures[tex], rec, des);
}

void SDL2VideoBackend::renderCopyEx(int tex, SDL_Rect* rec, SDL_Rect* des, double angle, SDL_Point* piv, SDL_RendererFlip flip) {
	if (tex < 0 || tex > static_cast<int>(mTextures.size()) - 1)
		return;

	SDL_RendererFlip a;

	SDL_RenderCopyEx(mRenderer, mTextures[tex], rec, des, angle, piv, flip);
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

	newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);

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
	
	newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
	
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

	if (mTextures.size() == 1) {
		mTextures.push_back(0);
	}

	// Add texture name

	while (mTextureNames.size() == 1) {
		mTextureNames.push_back("");
	}

	std::string name = path;
	std::string::size_type slashnum = path.find_last_of("/");
	
	if (slashnum != std::string::npos) {
		name = path.substr(slashnum + 1, name.length() - 1);
	}

	for (Uint32 i = 1; i < mTextureNames.size(); i++) {
		if (mTextureNames[i] == "") {
			mTextureNames[i] = name;
			mTextures[i] = nimg;
			return i;
		}
	}

	// Return the texture index
	
	mTextureNames.push_back(name);
	mTextures.push_back(nimg);

	return mTextures.size() - 1;
}

Uint32 SDL2VideoBackend::loadImageKeyed(const std::string& path, Uint32 key) {
	SDL_Texture* nimg = loadTextureKeyed(path, key);

	if (!nimg) {
		xyPrint("Unable to load file: %s", path.c_str());
		gvQuit = 1;
	}

	// Make sure vcTextures[0] == 0

	if (mTextures.size() == 1) {
		mTextures.push_back(0);
	}

	// Add texture name

	while (mTextureNames.size() == 1) {
		mTextureNames.push_back("");
	}

	std::string name = path;
	std::string::size_type slashnum = path.find_last_of("/");

	if (slashnum != std::string::npos) {
		name = path.substr(slashnum + 1, name.length() - 1);
	}

	for (Uint32 i = 1; i < mTextureNames.size(); i++) {
		if (mTextureNames[i] == "") {
			mTextureNames[i] = name;
			mTextures[i] = nimg;
			return i;
		}
	}

	// Return the texture index

	mTextureNames.push_back(name);
	mTextures.push_back(nimg);
	
	return mTextures.size() - 1;
}

void SDL2VideoBackend::deleteImage(Uint32 img) {
	if (img >= mTextures.size() || mTextures[img] == 0) {
		return;
	}

	SDL_DestroyTexture(mTextures[img]);

	if (img < mTextures.size() - 1) {
		mTextures[img] = 0;
		mTextureNames[img] = "";
		return;
	}

	mTextures.pop_back();
	mTextureNames.pop_back();
}

Uint32 SDL2VideoBackend::newTexture(Uint32 w, Uint32 h) {
	SDL_Texture* nimg = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

	if (!nimg) {
		xyPrint("Unable to create texture!");
		gvQuit = 1;
	}

	// Make sure vcTextures[0] == 0

	if (mTextures.size() == 1) {
		mTextures.push_back(0);
	}

	// Add texture name
	
	while (mTextureNames.size() == 1) {
		mTextureNames.push_back("");
	}

	for (Uint32 i = 1; i < mTextureNames.size(); i++) {
		if (mTextureNames[i] == "") {
			mTextureNames[i] = "new-texture-" + std::to_string(i);
			mTextures[i] = nimg;
			return i;
		}
	}

	// Return the texture index

	mTextureNames.push_back("new-texture-" + std::to_string(mTextures.size()));
	mTextures.push_back(nimg);

	return mTextures.size() - 1;
}

void SDL2VideoBackend::setScaling(float scale) {
	SDL_RenderSetScale(mRenderer, scale, scale);
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
	SDL_RenderSetViewport(mRenderer, &screensize);
	SDL_RenderSetLogicalSize(mRenderer, w, h);
	SDL_SetWindowSize(mWindow, w, h);
	SDL_SetWindowMinimumSize(mWindow, w, h);
}

int SDL2VideoBackend::screenW() {
	SDL_Rect vp;

	SDL_RenderGetViewport(mRenderer, &vp);

	return vp.w;
}

int SDL2VideoBackend::screenH() {
	SDL_Rect vp;

	SDL_RenderGetViewport(mRenderer, &vp);

	return vp.h;
}

int SDL2VideoBackend::windowW() {
	int w;

	SDL_GetWindowSize(mWindow, &w, 0);

	return w;
}

int SDL2VideoBackend::windowH() {
	int h;

	SDL_GetWindowSize(mWindow, 0, &h);

	return h;
}

void SDL2VideoBackend::toggleFullscreen() {
	SDL_SetWindowFullscreen(mWindow, (SDL_GetWindowFlags(mWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void* SDL2VideoBackend::getTextureAddr(int tex) {
	if (tex > 0 && tex < textureCount())
		return &mTextures[tex];
	
	return 0;
}

int SDL2VideoBackend::getTextureFilter(int tex) {
	SDL_ScaleMode sm = (SDL_ScaleMode)0;

	if(tex > 0 && tex < mTextures.size() && mTextures[tex] != 0)
		SDL_GetTextureScaleMode(mTextures[tex], &sm);
	else
		xyPrint("WARNING: Texture not found!");

	return (int)sm;
}

void SDL2VideoBackend::setTextureFilter(int tex, int filter) {
	SDL_ScaleMode sm = (SDL_ScaleMode)std::min(std::max(filter, 0), 2);

	if(tex > 0 && tex < mTextures.size() && mTextures[tex] != 0)
		SDL_SetTextureScaleMode(mTextures[tex], sm);
	else
		xyPrint("WARNING: Texture not found!");
}

void SDL2VideoBackend::setTextureBlendMode(int texture, int blend) {
	if (texture < 0 || texture > static_cast<int>(mTextures.size()) - 1) {
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

	SDL_SetTextureBlendMode(mTextures[texture], mode);
}

void SDL2VideoBackend::setTextureBlendMode(SDL_Texture* texture, int blend) {
	if (texture == NULL) {
		throw std::runtime_error("Invalid texture. Cannot set blend mode");
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

	SDL_SetTextureBlendMode(texture, mode);
}

void SDL2VideoBackend::setTextureColorMod(int tex, uint8_t r, uint8_t g, uint8_t b) {
	if (tex > 0 && tex < mTextures.size())
		SDL_SetTextureColorMod(mTextures[tex], r, g, b);
}

void SDL2VideoBackend::setTextureAlphaMod(int tex, uint8_t alpha) {
	if (tex > 0 && tex < mTextures.size())
		SDL_SetTextureAlphaMod(mTextures[tex], alpha);
}

void SDL2VideoBackend::queryTexture(int tex, int* width, int* height) {
	if (tex > 0 && tex < mTextures.size())
		SDL_QueryTexture(mTextures[tex], 0, 0, width, height);
}

std::string SDL2VideoBackend::getTextureName(int texture) {
	if (texture > 0 && texture < mTextureNames.size()) {
		return mTextureNames[texture];
	}

	return "";
}

int SDL2VideoBackend::findTexture(const std::string& name) {
	for (int i = 0; i < mTextureNames.size(); i++) {
		if (mTextureNames[i] == name) {
			return i;
		}
	}

	return 0;
}

void SDL2VideoBackend::printTextureNames() {
	for (int i = 0; i < mTextureNames.size(); i++) {
		xyPrint("%d - %s", i, mTextureNames[i].c_str());
	}
}

/** SHAPES */
void SDL2VideoBackend::drawCircle(int x, int y, int radius, bool filled) {
	if (filled)
		filledCircleColor(mRenderer, x, y, radius, gvDrawColor);
	else
		circleColor(mRenderer, x, y, radius, gvDrawColor);
}

void SDL2VideoBackend::drawRect(int x, int y, int w, int h, bool filled) {
	if (filled)
		boxColor(mRenderer, x, y, x + w, y + h, gvDrawColor);
	else
		rectangleColor(mRenderer, x, y, x + w, y + h, gvDrawColor);
}

// Draw a pixel

void SDL2VideoBackend::drawPoint(int x, int y) {
	pixelColor(mRenderer, x, y, gvDrawColor);
}

// Draw a line

void SDL2VideoBackend::drawLine(int x1, int y1, int x2, int y2) {
	thickLineColor(mRenderer, x1, y1, x2, y2, 1, gvDrawColor);
}

// Draw a thick line

void SDL2VideoBackend::drawLineWide(int x1, int y1, int x2, int y2, int w) {
	thickLineColor(mRenderer, x1, y1, x2, y2, w, gvDrawColor);
}

void SDL2VideoBackend::getScale(float* x, float* y) {
	SDL_RenderGetScale(mRenderer, x, y);
}

void SDL2VideoBackend::renderPresent() {
	SDL_RenderPresent(mRenderer);
}
