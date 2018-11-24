/*=============*\
| SPRITE SOURCE |
\*=============*/



#include "main.h"
#include "global.h"
#include "graphics.h"
#include "sprite.h"
#include "maths.h"

xySprite::xySprite(const char* filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, int pivotX, int pivotY, Uint32 _frames){
	//Set variables
	w = width;
	h = height;
	mar = margin;
	pad = padding;
	pvX = pivotX;
	pvY = pivotY;
	numero = 0;
	frames = _frames;
	tex = xyLoadImage(filename);
	name = filename;
	//SDL_QueryTexture(vcTextures[tex], format, 0, 0, 0); //// DO NOT USE! ////

	//Extract short file name
	name = filename;
	string::size_type slashnum = name.find_last_of("/");
	if(slashnum != string::npos) name = name.substr(slashnum, name.length() - 1);

	if(vcSprites.size() == 0){
		vcSprites.push_back(this);
		numero = 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < vcSprites.size(); i++){
			if(vcSprites[i] == 0){
				vcSprites[i] = this;
				numero = i;
				break;
			};
		};

		//If an open space wasn't found
		if(numero == 0){
			vcSprites.push_back(this);
			numero = vcSprites.size() - 1;
		};
	};

	//Parse the image for rows and colums
	int origW, origH;
	SDL_QueryTexture(vcTextures[tex], 0, 0, &origW, &origH);
	origW -= mar;
	origH -= mar;
	col = floor((float)(origW / (w + pad)));
	row = floor((float)(origH / (h + pad)));
	if(col < 1) col = 1;
	if(row < 1) row = 1;
	if(frames == 0) frames = col * row;
};

xySprite::~xySprite(){
	//Remove from list
	if(numero == vcSprites.size() - 1) vcSprites.pop_back();
	else vcSprites[numero] = 0;
};

void xySprite::draw(int f, int x, int y){
	int fd = xyWrap(f, 0, frames - 1);

    SDL_Rect rec;
    SDL_Rect des;

    des.x = x - pvX;
    des.y = y - pvY;
    des.w = w;
    des.h = h;

    int fx = fd % col;
    int fy = (fd - fx) / col;

    rec.x = mar + (fx * w) + (pad * fx);
    rec.y = mar + (fy * h) + (pad * fy);
    rec.w = w;
    rec.h = h;

    SDL_RenderCopy(gvRender, vcTextures[tex], &rec, &des);
};

void xySprite::drawex(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale){
	//Do nothing if scaling is set to 0 on either dimension
	if(xscale == 0 || yscale == 0) return;

	int fd = xyWrap(f, 0, frames - 1);

    SDL_Rect rec;
    SDL_Rect des;

    des.x = x - (pvX * xscale);
    des.y = y - (pvY * yscale);
    des.w = w * xscale;
    des.h = h * yscale;

    int fx = fd % col;
    int fy = (fd - fx) / col;

    rec.x = mar + (fx * w) + (pad * fx);
    rec.y = mar + (fy * h) + (pad * fy);
    rec.w = w;
    rec.h = h;

    SDL_Point *piv = new SDL_Point;
    piv->x = pvX * xscale;
    piv->y = pvY * yscale;

    SDL_RenderCopyEx(gvRender, vcTextures[tex], &rec, &des, (double)angle, piv, flip);
};

Uint32 xySprite::getnum(){
	return numero;
};

Uint32 xySprite::gettex(){
	return tex;
};

Uint32 xySprite::getframes(){
    return frames;
};

Uint32 xySprite::getw(){ return w; };
Uint32 xySprite::geth(){ return h; };
