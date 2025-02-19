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
| SPRITE HEADER |
\*=============*/

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "brux/main.hpp"

class xySprite {
private:
	Uint32 numero, mar, pad, w, h, tex, col, row, frames = 0;
	int osX, osY;
	float pvX, pvY;
	Uint32 *format;
public:
	bool didLoad;
	std::string name;
	std::string source;
	bool needsReload = false;
	SDL_BlendMode mode = SDL_BLENDMODE_BLEND;
	xySprite(const std::string& filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, float pivotX, float pivotY);
	xySprite(Uint32 texture, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, float pivotX, float pivotY);
	~xySprite();
	void replaceSprite(const std::string& filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, float pivotX, float pivotY);
	void draw(int f, int x, int y, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, float xscale = 1.0, float yscale = 1.0, float alpha = 1.0, Uint32 color = 0xFFFFFFFF);
	void drawex(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha);
	void drawmod(int f, int x, int y, Uint32 color);
	void drawexmod(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha, Uint32 color);

	void reload();
	void deload();

	Uint32 getnum() const { return numero; }
	Uint32 gettex() const { return tex; }
	Uint32 getframes() const { return frames; }
	Uint32 getw() const { return w; }
	Uint32 geth() const { return h; }
	Uint32 getrow() const { return row; }
	Uint32 getcol() const { return col; }
	const char* getname() const { return name.c_str(); }
};

/** API */
std::string xySpriteName(int sprite);
int xyFindSprite(const std::string& name);
int xyNewSprite(const std::string& i, int w, int h, float px, float py, int m, int p);
int xyNewSpriteFT(int t, int w, int h, float px, float py, int m, int p);
void xyDrawSprite(int i, int f, int x, int y);
void xyDrawSpriteEx(int i, int f, int x, int y, int a, int l, float sx, float sy, float p, int c);
void xyDrawSpriteMod(int i, int f, int x, int y, int c);
void xyDrawSpriteExMod(int i, int f, int x, int y, int a, int l, float sx, float sy, float p, int c);
void xyDeleteSprite(int i);
int xySpriteW(int i);
int xySpriteH(int i);
void xyReplaceSprite(int s, const std::string& f, int w, int h, int m, int p, float x, float y);
void xySpriteSetBlendMode(int sprite, int blend);
void xyFlushSprites();

void xyRegisterSpriteAPI(ssq::VM& vm);

#endif
