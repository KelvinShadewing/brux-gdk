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
| TEXT SOURCE |
\*===========*/

#include "brux/text.hpp"

#include <simplesquirrel/vm.hpp>

#include "brux/global.hpp"
#include "brux/graphics.hpp"
#include "brux/main.hpp"
#include "brux/sprite.hpp"

//New bitmap font format to replace SDL_ttf.
//
//When created, it takes an existing sprite
//to use as a bitmap font.
//
//Each frame of the sprite is scanned,
//checking each pixel column for transparency
//to find the minimum and maximum X
//coordinates containing pixels with alpha
//values above the threshold.
//
//Might be a good idea to bring back SDL_ttf
//to create bitmap fonts but use the same
//system either way to render.

xyFont::xyFont(Uint32 index, Uint32 firstchar, Uint8 threshold, bool monospace, int _kern) {
	//If there is no sprite that can be used, then cancel
	if(vcSprites.size() <= index || vcSprites[index] == 0) {
		xyPrint("The sprite does not exist!");
		delete this;
		return;
	}

	//Add to the list
	numero = -1;
	if(vcFonts.size() == 0) {
		vcFonts.push_back(this);
		numero = 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < static_cast<int>(vcFonts.size()); i++) {
			if(vcFonts[i] == 0) {
				vcFonts[i] = this;
				numero = i;
				break;
			}
		}

		//If an open space wasn't found
		if(numero == -1) {
			vcFonts.push_back(this);
			numero = static_cast<int>(vcFonts.size()) - 1;
		}
	}

	//Get the sprite
	source = vcSprites[index];

	//Get frame number and x/width
	cx.resize(source->getframes());
	cw.resize(source->getframes());

	if(cx.size() > 0) {
		for(Uint32 i = 0; i < source->getframes(); i++) {
			cx[i] = 0;
			cw[i] = source->getw();
		}
	}

	if(!monospace) {
		SDL_Surface* ts = IMG_Load(source->source.c_str());

		//Scan each frame to find the minimum and maximum X coordinates
		//with non-transparent pixels. This is done by scanning left to right
		//for the minimum and right to left for the maximum.

		//Loop through each frame
		for(Uint32 i = 1; i < source->getframes(); i++) {
			//Find the minimum X coordinate with non-transparent pixels
			Uint32 minx = source->getw();
			for(Uint32 j = 0; j < source->getw(); j++) {
				for(Uint32 k = 0; k < source->geth(); k++) {
					Uint8 a = xyGetAlpha(xyGetSurfacePixel(ts, j + ((i % source->getcol()) * source->getw()), k + (i / source->getcol() * source->geth())));
					if(a > threshold && j < minx) {
						minx = j;
						break;
					}
				}
			}
			cx[i] = minx;

			//Find the maximum X coordinate with non-transparent pixels
			Uint32 maxx = 0;
			for(Uint32 j = source->getw(); j > 0; j--) {
				for(Uint32 k = 0; k < source->geth(); k++) {
					Uint8 a = xyGetAlpha(xyGetSurfacePixel(ts, j + ((i % source->getcol()) * source->getw()), k + (i / source->getcol() * source->geth())));
					if(a > threshold && j > maxx) {
						maxx = j;
					}
				}
			}
			cw[i] = maxx + 1;
		}

		SDL_FreeSurface(ts);
	}

	start = firstchar;
	kern = _kern;
};

void xyFont::draw(int x, int y, std::string text) {
	int dx = x, dy = y; //Set cursor start position
	int c; //Current character by font index

	//Loop to end of std::string
	for(int i = 0; i < static_cast<int>(text.length()); i++) {
		if (text[i] == '\n') {
			dy += source->geth();
			dx = x;
		} /* else if(text[i] == '$' && i < text.length() - 2 && text[i + 1] == '{') {
			//Special character support using frames from other sprites
			//Syntax: ${sprite,frame}

			std::string s = "";
			std::string f = "";
			SQInteger snum = 0;

			i += 2;

			xyPrint("Print A");

			while(text[i] != '}') {
				//Get the sprite and frame number
				while(text[i] != ',' && text[i] != '}') {
					s += text[i];
					i++;
				}
				i++;
				while(text[i] != '}') {
					f += text[i];
					i++;
				}
				i++;
			}

			xyPrint("Print B");

			//Translate the sprite variable name to a number
			sq_pushstring(gvSquirrel.getHandle(), s.c_str(), -1);
			sq_get(gvSquirrel.getHandle(), -1);
			sq_getinteger(gvSquirrel.getHandle(), -1, &snum);
			sq_pop(gvSquirrel.getHandle(), 2);

			xySprite* tempSrc = vcSprites[snum];
			c = std::stoi(f);
			tempSrc->draw(c, dx, dy);
			dx += tempSrc->getw() + kern;
		}*/
		else {
			c = (int)text[i] - start; //Get current character and apply font offset
			source->draw(c, dx, dy);
			dx += cw[std::min(c, (int)cw.size() - 1)] + kern - cx[std::min(c, (int)cx.size() - 1)];
		}
	}
};

Uint32 xyFont::getnum() {
	return numero;
};


/** API */

int xyNewFont(int i, int c, int t, bool m, int k) {
	// Sanitize inputs
	if (i < 0) {
		i = 0;
	}
	else if (t > 255) {
		t = 255;
	}
	else if (c > 255) {
		c = 255;
	}

	xyFont* newfont = new xyFont(i, static_cast<char>(c), static_cast<unsigned char>(t), m, k);
	return newfont->getnum();
}

#define FONT_CHECK_VALID  if (f >= static_cast<int>(vcFonts.size()) || vcFonts[f] == 0) return

void xyDrawText(int f, float x, float y, const std::string& s) {
	FONT_CHECK_VALID;
	vcFonts[f]->draw(static_cast<int>(x), static_cast<int>(y), s);
}

#undef FONT_CHECK_VALID

std::string xyChint(int i) {
	return std::string(1, static_cast<char>(i));
}


void xyRegisterTextAPI(ssq::VM& vm) {
	vm.addFunc("newFont", xyNewFont); // Doc'd
	vm.addFunc("drawText", xyDrawText); // Doc'd
	vm.addFunc("chint", xyChint); // Doc'd
}
