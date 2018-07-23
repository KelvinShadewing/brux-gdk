/*===========*\
| TEXT SOURCE |
\*===========*/



#include "main.h"
#include "global.h"
#include "graphics.h"
#include "sprite.h"
#include "text.h"


/*
New bitmap font format to replace SDL_ttf.

When created, it takes an existing sprite
to use as a bitmap font.

Each frame of the sprite is scanned,
checking each pixel column for
transparency to find the minimum and
maximum X coordinates containing pixels
with alpha values above the threshold.
*/

xyFont::xyFont(Uint32 index, char firstchar, Uint8 threshold, bool monospace){
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
		if(numero == 0){
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
        for(int i = 0; i < cx.size(); i++){
            cx.push_back(0);
            cw.push_back(source->getw());
        };
	} else {//Dynamic (ignored until character scanning is done)
        //TODO: Get individual character width
	};
};

void draw(int x, int y, string text){

};
