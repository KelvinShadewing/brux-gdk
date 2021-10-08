/*===========*\
| TEXT SOURCE |
\*===========*/



#include "main.h"
#include "global.h"
#include "graphics.h"
#include "sprite.h"
#include "text.h"
#include "iconv.hpp"

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
	if(vcSprites.size() <= index) {
		xyPrint(0, "The sprite does not exist!");
		delete this;
		return;
	}

	if(vcSprites[index] == 0) {
		xyPrint(0, "The sprite does not exist!");
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
		for(int i = 1; i < vcFonts.size(); i++) {
			if(vcFonts[i] == 0) {
				vcFonts[i] = this;
				numero = i;
				break;
			}
		}

		//If an open space wasn't found
		if(numero == -1) {
			vcFonts.push_back(this);
			numero = vcFonts.size() - 1;
		}
	}

	//Get the sprite
	source = vcSprites[index];

	//Get frame number and x/width
	cx.resize(source->getframes());
	cw.resize(source->getframes());

	if(true){//Monospace
		if(cx.size() > 0) {
			for(int i = 0; i < source->getframes(); i++) {
				cx[i] = 0;
				cw[i] = source->getw();
			}
		}
	} else {	//Dynamic (ignored until character scanning is done)
		//TODO: Get individual character width

		//Get and store current render target
		SDL_Texture* ttex;
		ttex = SDL_GetRenderTarget(gvRender);

		//Make temporary texture
		SDL_Texture* worktex = SDL_CreateTexture(gvRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, source->getw(), source->geth());

		//Set render target to temp
		SDL_SetRenderTarget(gvRender, worktex);

		//For each frame in the source sprite
		for(int i = 0; i < source->getframes(); i++) {
			//Render current frame
			source->draw(i, 0, 0);

			//For each column in source width
			for(int j = 0; j < source->getw(); j++) {
				bool found = 0;

				//For each pixel in the column
				for(int k = 0; k < source->geth(); k++) {
					//If pixel alpha is above threshold, set cx here, then break
				}
			}

			//For each column in source width
			for(int j = 0; j < source->getw(); j++) {
				bool found = 0;

				//For each pixel in the column
				for(int k = 0; k < source->geth(); k++) {
					//If pixel alpha is above threshold, update cw to this coord minus cx, then break
				}
			}
			//Clear texture
		}
		//Delete temp texture
		//Reset render target to stored texture
	}

	start = firstchar;
	kern = _kern;
};

void xyFont::draw(int x, int y, string text) {
	int dx = x, dy = y; //Set cursor start position
	int c; //Current character by font index

	// by default, characters are handled in UTF-8 in C++. in order to support CP437, each character in the string has
	// to be converted to CP437 from UTF-8. so to do so, a converter using iconv.h is used. 
	// without said converter, this would require all sorts of bit manipulation and table-lookups 
	// to properly convert unicode stored in UTF-8 to the unicodes stored in CP437.
	iconvpp::converter conv("CP437", "UTF-8");
	std::string output;
	conv.convert(text, output);

	//Loop to end of string
	for(int i = 0; i < output.length(); i++) {
		if (output[i] == '\n') {
			dy += source->geth();
			dx = x;
		} else {
			//each character should only be a byte long, hence uint8_t
			uint8_t c = (uint8_t)output[i] - start;
			// characters that exceed ASCII have the most significant bit set to 1, so XORing against that bit
			// will give the proper index into a CP437 spritesheet.
			if (c < 0){
				c ^= 128;
			}

			if (c >= 0 && c < cw.size()){ //Is this character defined in the font?
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
