#include "api/graphics.hpp"

#include "brux/global.hpp"
#include "brux/graphics.hpp"

namespace BruxAPI {

//////////////
// GRAPHICS //
//////////////

void clearScreen() {
	SDL_RenderClear(gvRender);
}

void setDrawTarget(int tex) {
	xySetDrawTarget(tex);
	gvDrawTarget = tex;
}

int getDrawTarget() {
	return gvDrawTarget;
}

void resetDrawTarget() {
	xyResetDrawTarget();
}

void drawImage(int img, float x, float y) {
	xyDrawImage(img, x, y);
}

void drawImageEx(int img, float x, float y, float a, int f, float w, float h, float c) {
	xyDrawImageEx(img, x, y, a, static_cast<SDL_RendererFlip>(f), w, h, 0.f, c);
}

void setDrawColor(int color) {
	xySetDrawColor(color);
}

int loadImage(const std::string& file) {
	return xyLoadImage(file);
}

int loadImageKey(const std::string& file, int key) {
	return xyLoadImageKeyed(file, key);
}

void setBackgroundColor(int color) {
	xySetBackgroundColor(color);
}

void setScaling(float scale) {
	if (scale <= 0) return;

	SDL_RenderSetScale(gvRender, scale, scale);
}

void setScalingFilter(int hint) {
	if (hint > 2) hint = 2;
	if (hint < 0) hint = 0;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(hint).c_str());
}

void setResolution(int w, int h) {
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
}

int screenW() {
	SDL_Rect vp;
	SDL_RenderGetViewport(gvRender, &vp);
	return vp.w;
}

int screenH() {
	SDL_Rect vp;
	SDL_RenderGetViewport(gvRender, &vp);
	return vp.h;
}

int windowW() {
	int w;
	SDL_GetWindowSize(gvWindow, &w, 0);
	return w;
}

int windowH() {
	int h;
	SDL_GetWindowSize(gvWindow, 0, &h);
	return h;
}

int newTexture(int w, int h) {
	return xyNewTexture(w, h);
}

void textureSetBlendMode(int texture, int blend) {
	if (texture < 0 || texture > vcTextures.size() - 1) {
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
	};

	SDL_SetTextureBlendMode(vcTextures[texture], mode);
}

} // namespace BruxAPI
