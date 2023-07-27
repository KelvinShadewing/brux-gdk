//  Brux - Sprites API
//  Copyright (C) 2016 KelvinShadewing
//                2023 Vankata453
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

#include "api/sprites.hpp"

#include "brux/main.hpp"

#include "brux/global.hpp"
#include "brux/sprite.hpp"

namespace BruxAPI {

/////////////
// SPRITES //
/////////////

std::string spriteName(int sprite) {
	if(static_cast<int>(vcSprites.size()) <= sprite || sprite < 0 || vcSprites[sprite] == 0)
		return "N/A";

	return vcSprites[sprite]->name;
}

int findSprite(const std::string& name) {
	//xyPrint("Searching for sprite: %s", name.c_str());
	//xyPrint("Number of sprites to search: %i", vcSprites.size());

	for (size_t i = 0; i < vcSprites.size(); i++) {
		if (vcSprites[i] != 0) {
			//xyPrint("Current sprite name: %s", vcSprites[i]->getname());
			if (vcSprites[i]->getname() == name) {
				return vcSprites[i]->getnum();
			}
		}
	}

	return 0;
}

int newSprite(const std::string& i, int w, int h, int m, int p, float px, float py) {
	xySprite* newsprite = new xySprite(i, w, h, m, p, px, py);
	return newsprite->getnum();
}

int newSpriteFT(int t, int w, int h, int m, int p, float px, float py) {
	xySprite* newsprite = new xySprite(t, w, h, m, p, px, py);
	return newsprite->getnum();
}

/** Macros to help easily check if a sprite is valid. **/
#define SPRITE_CHECK_VALID       if (static_cast<int>(vcSprites.size()) <= i || vcSprites[i] == 0)
#define SPRITE_CHECK_VALID_VOID  SPRITE_CHECK_VALID return
#define SPRITE_CHECK_VALID_INT   SPRITE_CHECK_VALID return 0

void drawSprite(int i, int f, int x, int y) {
	SPRITE_CHECK_VALID_VOID;
	vcSprites[i]->draw(f, x, y);
}

void drawSpriteEx(int i, int f, int x, int y, int a, int l, float sx, float sy, float p) {
	SPRITE_CHECK_VALID_VOID;
	vcSprites[i]->drawex(f, x, y, a, static_cast<SDL_RendererFlip>(l), sx, sy, p);
}

void drawSpriteMod(int i, int f, int x, int y, int c) {
	SPRITE_CHECK_VALID_VOID;
	vcSprites[i]->drawmod(f, x, y, c);
}

void drawSpriteExMod(int i, int f, int x, int y, int a, int l, float sx, float sy, float p, int c) {
	SPRITE_CHECK_VALID_VOID;
	vcSprites[i]->drawexmod(f, x, y, a, static_cast<SDL_RendererFlip>(l), sx, sy, p, c);
}

void deleteSprite(int i) {
	SPRITE_CHECK_VALID_VOID;
	delete vcSprites[i];
}

int spriteW(int i) {
	SPRITE_CHECK_VALID_INT;
	return vcSprites[i]->getw();
}

int spriteH(int i) {
	SPRITE_CHECK_VALID_INT;
	return vcSprites[i]->geth();
}

void replaceSprite(int s, const std::string& f, int w, int h, int m, int p, float x, float y) {
	if (s <= 0 || s >= static_cast<int>(vcSprites.size())) return;

	if (vcSprites[s] != 0) {
		vcSprites[s]->replaceSprite(f, w, h, m, p, x, y);
	}
	else {
		vcSprites[s] = new xySprite(f, w, h, m, p, x, y);
	}
}

void spriteSetBlendMode(int sprite, int blend) {
	if (sprite < 0 || sprite > static_cast<int>(vcSprites.size()) - 1) {
		throw std::runtime_error("Invalid sprite ID. Cannot set blend mode");
	}

	SDL_BlendMode mode;
	switch (blend) {
		case 0:
			mode = SDL_BLENDMODE_NONE;
			break;
		case 1:
			mode = SDL_BLENDMODE_BLEND;
			break;
		case 2:
			mode = SDL_BLENDMODE_ADD;
			break;
		case 3:
			mode = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT, SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT);
			break;
		case 4:
			mode = SDL_BLENDMODE_MOD;
			break;
		default:
			mode = SDL_BLENDMODE_NONE;
			break;
	};

	SDL_SetTextureBlendMode(vcTextures[vcSprites[sprite]->gettex()], mode);
}

} // namespace BruxAPI
