/*===============*\
| GRAPHICS SOURCE |
\*===============*/


#include "main.h"
#include "global.h"
#include "graphics.h"
#include "fileio.h"

//////////
//SYSTEM//
//////////

//Clear screen
void xyClearScreen(){
	SDL_RenderClear(gvRender);
};


//Set draw color based on RGBA data
void xySetDrawColor(int r, int g, int b, int a){
	//Set color correction
	if(r > 255) r = 255;
	if(r < 0) r = 0;
	if(g > 255) g = 255;
	if(g < 0) g = 0;
	if(b > 255) b = 255;
	if(b < 0) b = 0;
	if(a > 255) a = 255;
	if(a < 0) r = 0;

	SDL_SetRenderDrawColor(gvRender, r, g, b, a);
};

//Set draw color from 24- or 32-bit integer
void xySetDrawColor(Uint32 color){
	//If the value of color is too big for a 24-bit integer, then treat it as 32-bit
	Uint8 r;
	if(color > 0xFFFFFF) r = (color >> 24) & 255;
	else r = (color >> 16) & 255;

	//Do the same for each color value
	Uint8 g;
	if(color > 0xFFFFFF) g = (color >> 16) & 255;
	else g = (color >> 8) & 255;

	Uint8 b;
	if(color > 0xFFFFFF) b = (color >> 8) & 255;
	else b = color & 255;

	//If it's not big enough for 32-bit, then use full alpha
	Uint8 a;
	if(color > 0xFFFFFF) a = color & 255;
	else a = 255;

	//Set the color
	SDL_SetRenderDrawColor(gvRender, r, g, b, a);
	gvDrawColor = color;
};


//Extract color value from a single integer
Uint8 xyGetRed(Uint32 color){
	Uint8 r;
	if(color > 0xFFFFFF) r = (color >> 24) & 255;
	else r = (color >> 16) & 255;

	return r;
};

Uint8 xyGetGreen(Uint32 color){
	Uint8 g;
	if(color > 0xFFFFFF) g = (color >> 16) & 255;
	else g = (color >> 8) & 255;

	return g;
};

Uint8 xyGetBlue(Uint32 color){
	Uint8 b;
	if(color > 0xFFFFFF) b = (color >> 8) & 255;
	else b = color & 255;

	return b;
};

void xySetBackgroundColor(Uint32 color){
	gvBackColor = color;
};

//....
void xyWait(int ticks){
	SDL_Delay(ticks);
};

//Set draw target to a texture
void xySetDrawTarget(Uint32 tex){
	if(vcTextures.size() >= tex || vcTextures[tex] != 0)
	SDL_SetRenderTarget(gvRender, vcTextures[tex]);
};

//Set draw target back to screen
void xyResetDrawTarget(){
	SDL_SetRenderTarget(gvRender, 0);
};





//////////
//IMAGES//
//////////

//Load image
SDL_Texture* xyLoadTexture(const char*  path){
	SDL_Texture* newTexture = 0;

	//Load the surface
	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == 0){
		xyPrint(0, "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	} else {
		//Make texture from surface
		newTexture = SDL_CreateTextureFromSurface(gvRender, loadedSurface);
		if(newTexture == 0){
			xyPrint(0, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		};

		//Delete old surface
		SDL_FreeSurface(loadedSurface);
	};

	return newTexture;
};

SDL_Texture* xyLoadTextureKeyed(const char*  path, Uint32 key){
	SDL_Texture* newTexture = 0;

	//Load the surface
	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == 0){
		xyPrint(0, "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	} else {
		Uint8 r = xyGetRed(key);
		Uint8 g = xyGetGreen(key);
		Uint8 b = xyGetBlue(key);
		SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, r, g, b));
		newTexture = SDL_CreateTextureFromSurface(gvRender, loadedSurface);
		if(newTexture == 0){
			xyPrint(0, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		};

		SDL_FreeSurface(loadedSurface);
	};

	return newTexture;
};

//Load a texture and assign it to a slot in the textures list
Uint32 xyLoadImage(const char* path){
	SDL_Texture* nimg = xyLoadTexture(path);

	if(!nimg){
		xyPrint(0, "Unable to load file: %s", path);
		gvQuit = 1;
	};

	//Make sure vcTextures[0] == 0
	if(vcTextures.size() == 1) vcTextures.push_back(0);

	for(Uint32 i = 1; i < vcTextures.size(); i++){
		if(vcTextures[i] == 0){
			vcTextures[i] = nimg;
			//Return the texture index
			return i;
		};
	};

	//Return the texture index
	vcTextures.push_back(nimg);
	return vcTextures.size() - 1;
};

Uint32 xyLoadImageKeyed(const char* path, Uint32 key){
	SDL_Texture* nimg = xyLoadTextureKeyed(path, key);

	if(!nimg){
		xyPrint(0, "Unable to load file: %s", path);
		gvQuit = 1;
	};

	//Make sure vcTextures[0] == 0
	if(vcTextures.size() == 1) vcTextures.push_back(0);

	for(Uint32 i = 1; i < vcTextures.size(); i++){
		if(vcTextures[i] == 0){
			vcTextures[i] = nimg;
			return i;
		};
	};

	vcTextures.push_back(nimg);
	return vcTextures.size() - 1;
};

//Draw image
void xyDrawImage(Uint32 tex, float x, float y){
	SDL_Rect rec;
	rec.x = x;
	rec.y = y;
	if(vcTextures.size() > tex){ //If the argument is in range
		if(vcTextures[tex] != 0){ //If the index points to an image
			SDL_QueryTexture(vcTextures[tex], 0, 0, &rec.w, &rec.h);
			SDL_RenderCopy(gvRender, vcTextures[tex], 0, &rec);
		};
	};
};

//Delete image
void xyDeleteImage(Uint32 tex){
	if(tex > vcSprites.size()) return;

	SDL_DestroyTexture(vcTextures[tex]);

	if(tex == vcSprites.size() - 1) vcSprites[tex] == 0; //Set the texture address to zero instead of removing it so other textures are not shifted over
	else vcSprites.pop_back(); //If it's the last one, then remove it to save memory
};

//Get FPS
Uint32 xyGetFPS(){
	Uint32 delay = SDL_GetTicks() - gvTicks;
	if(delay <= 0) return 1000;
	else return 1000 / delay;
};
