/*===========*\
| TEXT SOURCE |
\*===========*/



#include "main.h"
#include "global.h"
#include "graphics.h"
#include "sprite.h"
#include "text.h"

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
	uint16_t c; //Current character by index into the string
	// c is a uint16_t as the value may be shifted up to 12 bits to the left

	//Loop to end of string
	for(int i = 0; i < text.length(); i++) {
		if (text[i] == '\n') {
			dy += source->geth();
			dx = x;
		} else {
		  c = (uint8_t)text[i]; //get current character, which will only be 1 byte long

		  //in order to construct the unicode value of the character, first the number of
		  //bits in the first byte has to be identified, as this indicates how many bytes
		  //need to be used to reconstruct the value.

		  //the way this is indicated in UTF-8 is by the number of most significant bits
		  //in the value. the number of significant bits is the number of bytes to read in.

		  //a loop could probably be used in this case, but there are only two bit-masks
		  //that need to be checked against, and thus only 2 cases that need handling

		  // first check if there's a significant bit at all;
		  // the values masked against are chosen by their binary representation
		  if((c & 0x80) == 0x80){
		    //if the byte has 3 significant bits
		    if ((c & 0xE0) == 0xE0){
		      // due to the standard w/ UTF-8, there are guaranteed to be three bytes for
		      // the character stored in the string, so iterating the value of "i" twice is safe.
		      i += 1;
		      uint8_t c2 = (uint8_t)text[i]; // this is a uint16_t as a bit shift will be required
		      i += 1;
		      uint8_t c3 = (uint8_t)text[i]; // this is a uint8_t as a bit shift is not required

		      //now the most signficiant bits of each value need to be removed through XOR
		      //XOR the first 3 bits of the first byte
		      c ^= 0xE0;
		      //subsequent bytes have only 1 significant bit
		      //XOR the first bit of the second byte
		      c2 ^= 0x80;
		      //XOR the first bit of the third byte
		      c3 ^= 0x80;

		      //now the value is composed through bitshifts and ORing the value together

		      //shift the first byte left by 12 bits
		      c <<= 12;
		      //shift the second byte left by 6 bits
		      c2 <<= 6;
		      //OR the value of the first byte with the second
		      c |= c2;
		      //then OR the result with the value of the third byte
		      c |= c3;
		      // else if the byte has 2 significant bits
		    }else if ((c & 0xC0) == 0xC0){
		      // there are guaranteed to be two bytes for this character, so retrieve the next
		      i += 1;
		      uint8_t c2 = (uint8_t)text[i];
		      //XOR out the first two bits of the first byte
		      c ^= 0xC0;
		      //XOR out the first bit of the second byte
		      c2 ^= 0x80;
		      //shift the first byte left by 6 bits
		      c <<= 6;
		      //OR the value of the shifted first byte with the value of the XOR'd second
		      c |= c2;
		    }
		  }

		  // subtract by the start offset
		  c -= start;
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
