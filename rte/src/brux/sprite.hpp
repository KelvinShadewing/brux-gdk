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
	uint32_t numero, mar, pad, w, h, tex, col, row, frames = 0;
	bool didLoad;
	int osX, osY;
	float pvX, pvY;
	uint32_t *format;
public:
	std::string name;
	std::string source;
	xySprite(const std::string& filename, uint32_t width, uint32_t height, uint32_t margin, uint32_t padding, float pivotX, float pivotY);
	xySprite(uint32_t texture, uint32_t width, uint32_t height, uint32_t margin, uint32_t padding, float pivotX, float pivotY);
	~xySprite();
	void replaceSprite(const std::string& filename, uint32_t width, uint32_t height, uint32_t margin, uint32_t padding, float pivotX, float pivotY);
	void draw(int f, int x, int y);
	void drawex(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha);
	void drawmod(int f, int x, int y, uint32_t color);
	void drawexmod(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha, uint32_t color);\

	uint32_t getnum() const { return numero; }
	uint32_t gettex() const { return tex; }
	uint32_t getframes() const { return frames; }
	uint32_t getw() const { return w; }
	uint32_t geth() const { return h; }
	const char* getname() const { return name.c_str(); }
};

/** API */
std::string xySpriteName(int sprite);
int xyFindSprite(const std::string& name);
int xyNewSprite(const std::string& i, int w, int h, float px, float py, int m, int p);
int xyNewSpriteFT(int t, int w, int h, float px, float py, int m, int p);
void xyDrawSprite(int i, int f, int x, int y);
void xyDrawSpriteEx(int i, int f, int x, int y, int a, int l, float sx, float sy, float p);
void xyDrawSpriteMod(int i, int f, int x, int y, int c);
void xyDrawSpriteExMod(int i, int f, int x, int y, int a, int l, float sx, float sy, float p, int c);
void xyDeleteSprite(int i);
int xySpriteW(int i);
int xySpriteH(int i);
void xyReplaceSprite(int s, const std::string& f, int w, int h, int m, int p, float x, float y);
void xySpriteSetBlendMode(int sprite, int blend);

void xyRegisterSpriteAPI(ssq::VM& vm);

#endif
