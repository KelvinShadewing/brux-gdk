/*===========*\
| TEXT SOURCE |
\*===========*/



#include "main.h"
#include "global.h"
#include "graphics.h"
#include "text.h"


//Draw text
void xyDrawText(float x, float y, const char* text, Uint32 font, Uint32 color, int halign, int valign){
	//Get the draw color
	SDL_Color dCol = {xyGetRed(color), xyGetGreen(color), xyGetBlue(color)};

	//Create surface for rendering
	SDL_Surface* textSurface = TTF_RenderText_Solid(vcFonts[font], text, dCol);
	if(textSurface == 0){
		xyError(0, "Unable to render surface! SDL_ttf error: %s\n", TTF_GetError());
		return;
	};

	//Turn the surface into a texture
	SDL_Texture *mTexture = SDL_CreateTextureFromSurface(gvRender, textSurface);
	if(mTexture == 0){
		xyError(0, "Unable to create texture from surface! SDL_ttf error: %s\n", TTF_GetError());
		return;
	};
	int mW = textSurface->w;
	int mH = textSurface->h;
	SDL_Rect srcR = {0, 0, mW, mH};
	SDL_Rect desR = {x - ((mW / 2) * halign), y - ((mH / 2) * valign), mW, mH};
	SDL_FreeSurface(textSurface); //We're done with the surface now

	//Render the texture
	SDL_RenderCopy(gvRender, mTexture, &srcR, &desR);
	SDL_DestroyTexture(mTexture);
};

//Load font
Uint32 xyOpenFont(const char* filename, Uint32 size){
	//Attempt to load new font
	TTF_Font* newfont = TTF_OpenFont(filename, size);
	if(newfont == 0){
		xyError(0, "Failed to open TTF! SDL_ttf error: %s\n", TTF_GetError());
		return 0;
	};

	//Add new font to the list
	if(vcFonts.size() == 0){ //Add to end
		vcFonts.push_back(newfont);
		return vcFonts.size() - 1;
	} else for(int i = 0; i <= vcFonts.size(); i++){
		if(i == vcFonts.size()){ //Add to end
			vcFonts.push_back(newfont);
			return vcFonts.size() - 1;
		}else if(vcFonts[i] == 0){ //Add to middle
			vcFonts[i] = newfont;
			return i;
		};
	};
};

//Delete font
void xyCloseFont(Uint32 font){
	//Make sure the font ID is in range
	if(font >= vcFonts.size()) return;

	//Delete the font and remove the ID from vcFonts
	TTF_CloseFont(vcFonts[font]);
	vcFonts[font] = 0;
};