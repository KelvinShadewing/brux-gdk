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

#ifdef DO_NOT_INCLUDE //Dynamic (ignored until character scanning is done)
	//TODO: Get individual character width

	//Get and store current render target
	SDL_Texture* ttex;
	ttex = SDL_GetRenderTarget(gvRender);

	//Make temporary texture
	SDL_Texture* worktex = SDL_CreateTexture(gvRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, source->getw(), source->geth());

	//Set render target to temp
	SDL_SetRenderTarget(gvRender, worktex);

	//For each frame in the source sprite
	for(Uint32 i = 0; i < source->getframes(); i++) {
		//Render current frame
		SDL_RenderClear(gvRender);
		source->draw(i, 0, 0);

		//For each column in source width
		for(Uint32 j = 0; j < source->getw(); j++) {
			bool found = 0;

			//For each pixel in the column
			for(Uint32 k = 0; k < source->geth(); k++) {
				//If pixel alpha is above threshold, set cx here, then break
			}
		}

		//For each column in source width
		for(Uint32 j = 0; j < source->getw(); j++) {
			bool found = 0;

			//For each pixel in the column
			for(Uint32 k = 0; k < source->geth(); k++) {
				//If pixel alpha is above threshold, update cw to this coord minus cx, then break
			}
		}
		//Clear texture
	}
	//Delete temp texture
	//Reset render target to stored texture
#endif

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
		} else {
			c = (int)text[i] - start; //Get current character and apply font offset
			if (c >= 0 && c < static_cast<int>(cw.size())){ //Is this character defined in the font?
				source->draw(c, dx, dy);
				dx += cw[c] + kern;
			} else {
				// undefined characters should be blank
				dx += source->getw() + kern;
			}
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
