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

class xySprite
{
private:
	Uint32 numero, mar, pad, w, h, tex, col, row, frames = 0;
	bool didLoad;
	int osX, osY;
	float pvX, pvY;
	Uint32 *format;
public:
	std::string name;
	xySprite(const std::string& filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, int pivotX, int pivotY);
	xySprite(Uint32 texture, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, int pivotX, int pivotY);
	~xySprite();
	void replaceSprite(const std::string& filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, int pivotX, int pivotY);
	void draw(int f, int x, int y);
	void drawex(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha);
	void drawmod(int f, int x, int y, Uint32 color);
	void drawexmod(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha, Uint32 color);
	Uint32 getnum();
	Uint32 gettex();
	Uint32 getframes();
	Uint32 getw();
	Uint32 geth();
	const char* getname();
};

#endif
