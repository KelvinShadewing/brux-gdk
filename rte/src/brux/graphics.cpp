/*===============*\
| GRAPHICS SOURCE |
\*===============*/


#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/graphics.hpp"
#include "brux/fileio.hpp"

//////////
//SYSTEM//
//////////

//Clear screen
void xyClearScreen() {
	SDL_RenderClear(gvRender);
};


//Set draw color based on RGBA data
void xySetDrawColor(int r, int g, int b, int a) {
	//Set color correction
	if(r > 255) r = 255;
	if(r < 0) r = 0;
	if(g > 255) g = 255;
	if(g < 0) g = 0;
	if(b > 255) b = 255;
	if(b < 0) b = 0;
	if(a > 255) a = 255;
	if(a < 0) a = 0;

	Uint8 _r = r, _g = g, _b = b, _a = a;

	SDL_SetRenderDrawColor(gvRender, _r, _g, _b, _a);
};

//Set draw color from 24- or 32-bit integer
void xySetDrawColor(SQInteger color) {
	//If the value of color is too big for a 24-bit integer, then treat it as 32-bit
	Uint8 r;
	r = ((color & 0xFF000000) >> 24);

	//Do the same for each color value
	Uint8 g;
	g = ((color & 0x00FF0000) >> 16);

	Uint8 b;
	b = ((color & 0x0000FF00) >> 8);

	Uint8 a;
	a = color & 0x000000FF;

	//Set the color
	SDL_SetRenderDrawColor(gvRender, r, g, b, a);
	gvDrawColor = color;
	if(SDL_BYTEORDER == SDL_LIL_ENDIAN) gvDrawColor = SDL_Swap32(gvDrawColor);
};


//Extract color value from a single integer
Uint8 xyGetRed(Uint32 color) {
	Uint8 r;
	r = (color & 0xFF000000) >> 24;

	return r;
};

Uint8 xyGetGreen(Uint32 color) {
	Uint8 g;
	g = (color & 0x00FF0000) >> 16;

	return g;
};

Uint8 xyGetBlue(Uint32 color) {
	Uint8 b;
	b = (color & 0x0000FF00) >> 8;

	return b;
};

Uint8 xyGetAlpha(Uint32 color) {
	Uint8 a;
	a = color & 0x000000FF;

	return a;
};

void xySetBackgroundColor(Uint32 color) {
	gvBackColor = color;
};

//....
void xyWait(int ticks) {
	SDL_Delay(ticks);
};

//Set draw target to a texture
void xySetDrawTarget(Uint32 tex) {
	if(vcTextures.size() >= tex || vcTextures[tex] != 0)
	SDL_SetRenderTarget(gvRender, vcTextures[tex]);
};

//Set draw target back to screen
void xyResetDrawTarget() {
	SDL_SetRenderTarget(gvRender, 0);
};



//////////
//IMAGES//
//////////

//Load image
SDL_Texture* xyLoadTexture(const std::string& path) {
	SDL_Texture* newTexture = 0;

	//Load the surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == 0) {
		xyPrint(0, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		//Make texture from surface
		newTexture = SDL_CreateTextureFromSurface(gvRender, loadedSurface);
		if(newTexture == 0) {
			xyPrint(0, "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Delete old surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
};

SDL_Texture* xyLoadTextureKeyed(const std::string& path, Uint32 key) {
	SDL_Texture* newTexture = 0;

	//Load the surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == 0) {
		xyPrint(0, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		Uint8 r = xyGetRed(key);
		Uint8 g = xyGetGreen(key);
		Uint8 b = xyGetBlue(key);
		SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, r, g, b));
		newTexture = SDL_CreateTextureFromSurface(gvRender, loadedSurface);
		if(newTexture == 0) {
			xyPrint(0, "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
};

//Load a texture and assign it to a slot in the textures list
Uint32 xyLoadImage(const std::string& path) {
	SDL_Texture* nimg = xyLoadTexture(path.c_str());

	if(!nimg) {
		xyPrint(0, "Unable to load file: %s", path.c_str());
		gvQuit = 1;
	}

	//Make sure vcTextures[0] == 0
	if(vcTextures.size() == 1) vcTextures.push_back(0);

	//Return the texture index
	vcTextures.push_back(nimg);
	return vcTextures.size() - 1;
};

Uint32 xyLoadImageKeyed(const std::string& path, Uint32 key) {
	SDL_Texture* nimg = xyLoadTextureKeyed(path, key);

	if(!nimg) {
		xyPrint(0, "Unable to load file: %s", path.c_str());
		gvQuit = 1;
	}

	//Make sure vcTextures[0] == 0
	if(vcTextures.size() == 1) vcTextures.push_back(0);

	for(Uint32 i = 1; i < vcTextures.size(); i++) {
		if(vcTextures[i] == 0) {
			vcTextures[i] = nimg;
			return i;
		}
	}

	vcTextures.push_back(nimg);
	return vcTextures.size() - 1;
};

//Draw image
void xyDrawImage(Uint32 tex, float x, float y) {
	SDL_Rect rec;
	rec.x = x;
	rec.y = y;
	if(vcTextures.size() > tex) { //If the argument is in range)
		if(vcTextures[tex] != 0) { //If the index points to an image)
			SDL_QueryTexture(vcTextures[tex], 0, 0, &rec.w, &rec.h);
			SDL_RenderCopy(gvRender, vcTextures[tex], 0, &rec);
		}
	}
};

void xyDrawImageEx(Uint32 tex, float x, float y, float angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha, Uint32 color) {
	SDL_Rect rec;
	rec.x = 0;
	rec.y = 0;

	SDL_Rect des;
	des.x = x;
	des.y = y;

	//Break color into 8-bit versions
	Uint8 r, g, b;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;

	SDL_Point *piv = new SDL_Point;
	piv->x = 0;
	piv->y = 0;


	if(vcTextures.size() > tex) { //If the argument is in range)
		if(vcTextures[tex] != 0) { //If the index points to an image)
			SDL_QueryTexture(vcTextures[tex], 0, 0, &rec.w, &rec.h);
			des.w = rec.w * xscale;
			des.h = rec.h * yscale;
			SDL_SetTextureColorMod(vcTextures[tex], r, g, b);
			SDL_SetTextureAlphaMod(vcTextures[tex], alpha * 255);
			SDL_RenderCopyEx(gvRender, vcTextures[tex], &rec, &des, (double)angle, piv, flip);
			SDL_SetTextureAlphaMod(vcTextures[tex], 255);
			SDL_SetTextureColorMod(vcTextures[tex], 255, 255, 255);
		}
	}
};

//Delete image
void xyDeleteImage(Uint32 tex) {
	if(tex > vcTextures.size()) return;

	SDL_DestroyTexture(vcTextures[tex]);
	if(tex < vcTextures.size() - 1) vcTextures[tex] = 0;
	else vcTextures.pop_back();
};

//Get FPS
Uint32 xyGetFPS() {
	return gvFPS;
};

//Load a texture and assign it to a slot in the textures list
Uint32 xyNewTexture(Uint32 w, Uint32 h) {
	SDL_Texture* nimg = SDL_CreateTexture( gvRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h );

	if(!nimg) {
		xyPrint(0, "Unable to create texture!");
		gvQuit = 1;
	}

	//Make sure vcTextures[0] == 0
	if(vcTextures.size() == 1) vcTextures.push_back(0);

	for(Uint32 i = 1; i < vcTextures.size(); i++) {
		if(vcTextures[i] == 0) {
			vcTextures[i] = nimg;
			//Return the texture index
			return i;
		}
	}

	//Return the texture index
	vcTextures.push_back(nimg);
	return vcTextures.size() - 1;
};



//////////////
// GEOMETRY //
//////////////




