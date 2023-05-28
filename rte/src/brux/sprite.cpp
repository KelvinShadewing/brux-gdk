//  Brux - Sprite
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

/*=============*\
| SPRITE SOURCE |
\*=============*/

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/graphics.hpp"
#include "brux/sprite.hpp"
#include "brux/maths.hpp"

xySprite::xySprite(const std::string& filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, float pivotX, float pivotY) :
	w(width),
	h(height),
	mar(margin),
	pad(padding),
	pvX(pivotX),
	pvY(pivotY),
	numero(0),
	frames(),
	tex(xyLoadImage(filename)),
	name(filename)
{
	//SDL_QueryTexture(vcTextures[tex], format, 0, 0, 0); //// DO NOT USE! ////

	//Extract short file name
	std::string::size_type slashnum = name.find_last_of("/");
	if(slashnum != std::string::npos)
		name = name.substr(slashnum + 1, name.length() - 1);

	//Add sprite to list

	if(vcSprites.size() == 0) {
		vcSprites.push_back(this);
		numero = 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < static_cast<int>(vcSprites.size()); i++) {
			if(vcSprites[i] == 0) {
				vcSprites[i] = this;
				numero = i;
				break;
			}
		}

		//If an open space wasn't found
		if(numero == 0) {
			vcSprites.push_back(this);
			numero = static_cast<int>(vcSprites.size()) - 1;
		}
	}

	//Parse the image for rows and colums
	int origW, origH;
	SDL_QueryTexture(vcTextures[tex], 0, 0, &origW, &origH);
	origW -= mar;
	origH -= mar;
	col = static_cast<int>(std::floor(origW / (w + pad)));
	row = static_cast<int>(std::floor(origH / (h + pad)));
	if(col < 1) col = 1;
	if(row < 1) row = 1;
	frames = col * row;
};

xySprite::xySprite(Uint32 texture, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, float pivotX, float pivotY) :
	w(width),
	h(height),
	mar(margin),
	pad(padding),
	pvX(pivotX),
	pvY(pivotY),
	numero(0),
	frames(),
	tex(),
	name("texture")
{
	//SDL_QueryTexture(vcTextures[tex], format, 0, 0, 0); //// DO NOT USE! ////

	//Load texture
	if(texture >= 0 && texture < vcTextures.size()) {
		if(vcTextures[texture] != 0) tex = texture;
		else tex = 0;
	}

	//Add sprite to list

	if(vcSprites.size() == 0) {
		vcSprites.push_back(this);
		numero = 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < static_cast<int>(vcSprites.size()); i++) {
			if(vcSprites[i] == 0) {
				vcSprites[i] = this;
				numero = i;
				break;
			}
		}

		//If an open space wasn't found
		if(numero == 0) {
			vcSprites.push_back(this);
			numero = static_cast<int>(vcSprites.size()) - 1;
		}
	}

	//Parse the image for rows and colums
	int origW, origH;
	SDL_QueryTexture(vcTextures[tex], 0, 0, &origW, &origH);
	origW -= mar;
	origH -= mar;
	col = static_cast<int>(std::floor(origW / (w + pad)));
	row = static_cast<int>(std::floor(origH / (h + pad)));
	if(col < 1) col = 1;
	if(row < 1) row = 1;
	frames = col * row;
};

void xySprite::replaceSprite(const std::string& filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, float pivotX, float pivotY) {
	//Set variables
	w = width;
	h = height;
	mar = margin;
	pad = padding;
	pvX = pivotX;
	pvY = pivotY;
	numero = 0;
	frames = 0; //Obsolete, will untangle later
	Uint32 newtex = xyLoadImage(filename);
	//SDL_QueryTexture(vcTextures[tex], format, 0, 0, 0); //// DO NOT USE! ////

	//Delete old texture
	xyDeleteImage(tex);
	tex = newtex;

	//Extract short file name
	name = filename;
	std::string::size_type slashnum = name.find_last_of("/");
	if(slashnum != std::string::npos)
		name = name.substr(slashnum + 1, name.length() - 1);

	//Parse the image for rows and colums
	int origW, origH;
	SDL_QueryTexture(vcTextures[tex], 0, 0, &origW, &origH);
	origW -= mar;
	origH -= mar;
	col = static_cast<int>(std::floor(origW / (w + pad)));
	row = static_cast<int>(std::floor(origH / (h + pad)));
	if(col < 1) col = 1;
	if(row < 1) row = 1;
	frames = col * row;
};

xySprite::~xySprite() {
	//Remove from list
	if(numero == vcSprites.size() - 1) vcSprites.pop_back(); else vcSprites[numero] = 0;
	xyDeleteImage(tex);
};

void xySprite::draw(int f, int x, int y) {
	int fd = static_cast<int>(xyWrap(static_cast<float>(f), 0, static_cast<float>(frames) - 1));

	SDL_Rect rec;
	SDL_Rect des;

	des.x = x - static_cast<int>(pvX);
	des.y = y - static_cast<int>(pvY);
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

void xySprite::drawex(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha) {
	//Do nothing if scaling is set to 0 on either dimension
	if(xscale == 0 || yscale == 0) return;

	int fd = static_cast<int>(xyWrap(static_cast<float>(f), 0, static_cast<float>(frames) - 1));

	SDL_Rect rec;
	SDL_Rect des;

	//Temporary new pivots to be changed based on flip
	float npvX = pvX;
	float npvY = pvY;

	if(flip & SDL_FLIP_HORIZONTAL) {
		npvX = w - pvX;
	}
	if(flip & SDL_FLIP_VERTICAL) {
		npvY = h - pvY;
	}

	des.x = x - static_cast<float>(npvX * xscale);
	des.y = y - static_cast<float>(npvY * yscale);
	des.w = w * static_cast<float>(xscale);
	des.h = h * static_cast<float>(yscale);

	int fx = fd % col;
	int fy = (fd - fx) / col;

	rec.x = mar + (fx * w) + (pad * fx);
	rec.y = mar + (fy * h) + (pad * fy);
	rec.w = w;
	rec.h = h;

	SDL_Point *piv = new SDL_Point;
	piv->x = static_cast<int>(npvX * xscale);
	piv->y = static_cast<int>(npvY * yscale);

	SDL_SetTextureAlphaMod(vcTextures[tex], static_cast<Uint8>(alpha * 255));
	SDL_RenderCopyEx(gvRender, vcTextures[tex], &rec, &des, (double)angle, piv, flip);
	SDL_SetTextureAlphaMod(vcTextures[tex], 255);

	delete piv;
};

void xySprite::drawmod(int f, int x, int y, Uint32 color) {
	int fd = static_cast<int>(xyWrap(static_cast<float>(f), 0, static_cast<float>(frames) - 1));

	SDL_Rect rec;
	SDL_Rect des;

	des.x = x - static_cast<int>(pvX);
	des.y = y - static_cast<int>(pvY);
	des.w = w;
	des.h = h;

	int fx = fd % col;
	int fy = (fd - fx) / col;

	rec.x = mar + (fx * w) + (pad * fx);
	rec.y = mar + (fy * h) + (pad * fy);
	rec.w = w;
	rec.h = h;

	//Break color into 8-bit versions
	Uint8 r, g, b;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;

	SDL_SetTextureColorMod(vcTextures[tex], r, g, b);
	SDL_RenderCopy(gvRender, vcTextures[tex], &rec, &des);
	SDL_SetTextureColorMod(vcTextures[tex], 255, 255, 255);
};

void xySprite::drawexmod(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha, Uint32 color) {
	//Do nothing if scaling is set to 0 on either dimension
	if(xscale == 0 || yscale == 0) return;

	int fd = static_cast<int>(xyWrap(static_cast<float>(f), 0, static_cast<float>(frames) - 1));

	//Temporary new pivots to be changed based on fliip
	float npvX = pvX;
	float npvY = pvY;

	if(flip & SDL_FLIP_HORIZONTAL) {
		npvX = w - pvX;
	}
	if(flip & SDL_FLIP_VERTICAL) {
		npvY = h - pvY;
	}

	SDL_Rect rec;
	SDL_Rect des;

	des.x = x - static_cast<float>(npvX * xscale);
	des.y = y - static_cast<float>(npvY * yscale);
	des.w = w * static_cast<float>(xscale);
	des.h = h * static_cast<float>(yscale);

	int fx = fd % col;
	int fy = (fd - fx) / col;

	rec.x = mar + (fx * w) + (pad * fx);
	rec.y = mar + (fy * h) + (pad * fy);
	rec.w = w;
	rec.h = h;

	SDL_Point *piv = new SDL_Point;
	piv->x = static_cast<int>(npvX * xscale);
	piv->y = static_cast<int>(npvY * yscale);

	//Break color into 8-bit versions
	Uint8 r, g, b;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;

	SDL_SetTextureColorMod(vcTextures[tex], r, g, b);
	SDL_SetTextureAlphaMod(vcTextures[tex], static_cast<Uint8>(alpha * 255));
	SDL_RenderCopyEx(gvRender, vcTextures[tex], &rec, &des, (double)angle, piv, flip);
	SDL_SetTextureAlphaMod(vcTextures[tex], 255);
	SDL_SetTextureColorMod(vcTextures[tex], 255, 255, 255);

	delete piv;
};
