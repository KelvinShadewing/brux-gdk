//  Brux - Text
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

/*===========*\
| TEXT HEADER |
\*===========*/

#ifndef _TEXT_H_
#define _TEXT_H_

#include "brux/sprite.hpp"

class xyFont
{
private:
	xySprite* source;
	std::vector<int> cx;
	std::vector<int> cw;
	Uint32 start;
	Uint32 numero;
	bool mono;
	int kern; //Kerning can be negative since some fonts need to overlap a bit

public:
	xyFont(Uint32 index, Uint32 firstchar, Uint8 threshold, bool monospace, int _kern);
	Uint32 getnum();
	void draw(int x, int y, std::string text, Uint32 color = 0xffffffff);
};

/** API */
int xyNewFont(int i, int c, int t, bool m, int k);
void xyDrawText(int f, float x, float y, const std::string& s, Uint32 c = 0xffffffff);
std::string xyChint(int i);

void xyRegisterTextAPI(ssq::VM& vm);

#endif
