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

xyFont::xyFont(Uint32 index, Uint32 firstchar, Uint8 threshold, bool monospace){
	//If there is no sprite that can be used, then cancel
    if(vcSprites.size() <= index){
		xyPrint(0, "The sprite does not exist!");
		delete this;
		return;
	};
    if(vcSprites[index] == 0){
    	xyPrint(0, "The sprite does not exist!");
		delete this;
		return;
    };

    //Add to the list
	numero = -1;
	if(vcFonts.size() == 0){
		vcFonts.push_back(this);
		numero = 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < vcFonts.size(); i++){
			if(vcFonts[i] == 0){
				vcFonts[i] = this;
				numero = i;
				break;
			};
		};

		//If an open space wasn't found
		if(numero == -1){
			vcFonts.push_back(this);
			numero = vcFonts.size() - 1;
		};
	};

	//Get the sprite
	source = vcSprites[index];

	//Get frame number and x/width
	cx.resize(source->getframes());
	cw.resize(source->getframes());
	if(true){//Monospace
		if(cx.size() > 0){
			for(int i = 0; i < source->getframes(); i++){
				cx[i] = 0;
				cw[i] = source->getw();
			};
        };
	} else {//Dynamic (ignored until character scanning is done)
        //TODO: Get individual character width
	};

	start = firstchar;
};

void xyFont::draw(int x, int y, string text){
	int dx = x, dy = y; //Set cursor start position
	int c; //Current character by font index

	//Loop to end of string
	for(int i = 0; i < text.length(); i++){
		if (text[i] == '\n'){
			dy += source->geth();
			dx = x;
		} else {
			c = (int)text[i] - start; //Get current character and apply font offset
			if (c >= 0 && c < cw.size()){ //Is this character defined in the font?
				source->draw(c, dx, dy);
				dx += cw[c];
			} else {
				// undefined characters should be blank
				dx += source->getw();
			};
		};
	};
};

Uint32 xyFont::getnum(){
	return numero;
};
