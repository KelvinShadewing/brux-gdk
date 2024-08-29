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
	uint32_t start;
	uint32_t numero;
	bool mono;
	int kern; //Kerning can be negative since some fonts need to overlap a bit

public:
	xyFont(uint32_t index, uint32_t firstchar, uint8_t threshold, bool monospace, int _kern);
	uint32_t getnum();
	void draw(int x, int y, std::string text);
};

/** API */
int xyNewFont(int i, int c, int t, bool m, int k);
void xyDrawText(int f, float x, float y, const std::string& s);
std::string xyChint(int i);

void xyRegisterTextAPI(ssq::VM& vm);

#endif
