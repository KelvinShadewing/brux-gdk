//  Brux - Graphics API
//  Copyright (C) 2016 KelvinShadewing
//                2023 Vankata453
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

void drawImage(int img, int x, int y) {
	xyDrawImage(img, x, y);
}

void drawImagePart(int img, int x, int y, int ox, int oy, int w, int h) {
	xyDrawImagePart(img, x, y, ox, oy, w, h);
}

void drawImageEx(int img, int x, int y, float a, int f, int w, int h, int c) {
	xyDrawImageEx(img, x, y, a, static_cast<SDL_RendererFlip>(f), w, h, 0, c);
}

void setDrawColor(int color) {
	xySetDrawColor(color);
}

int loadImage(const std::string& file) {
	return xyLoadImage(file);
}

// Originally this was named loadImageKey, although that seems to be a typo - the documentation says it's getImageKeyed.
// I discovered that by running the test suite and noticing the missing function.

int loadImageKeyed(const std::string& file, int key) {
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
	};

	SDL_SetTextureBlendMode(vcTextures[texture], mode);
}

int findTexture(const std::string& name) {
	for(int i = 0; i < vcTextureNames.size(); i++) {
		if(vcTextureNames[i] == name) return i;
	}

	return 0;
}

std::string getTextureName(int texture) {
	if(texture > 0 && texture < vcTextureNames.size())
		return vcTextureNames[texture];
	else
		return "";
}

void printTextureNames() {
	for(int i = 0; i < vcTextureNames.size(); i++)
		xyPrint(0, "%d - %s", i, vcTextureNames[i].c_str());
}

} // namespace BruxAPI
