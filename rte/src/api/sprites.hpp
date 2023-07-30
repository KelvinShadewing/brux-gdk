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

#ifndef BRUX_API_SPRITES_HEADER
#define BRUX_API_SPRITES_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

/////////////
// SPRITES //
/////////////

std::string spriteName(int sprite); // Doc'd
int findSprite(const std::string& name); // Doc'd
int newSprite(const std::string& i, int w, int h, int m, int p, float px, float py); // Doc'd
int newSpriteFT(int t, int w, int h, int m, int p, float px, float py);
void drawSprite(int i, int f, int x, int y); // Doc'd
void drawSpriteEx(int i, int f, int x, int y, int a, int l, float sx, float sy, float p); // Doc'd
void drawSpriteMod(int i, int f, int x, int y, int c); // Doc'd
void drawSpriteExMod(int i, int f, int x, int y, int a, int l, float sx, float sy, float p, int c); // Doc'd
void deleteSprite(int i); // Doc'd
int spriteW(int i); // Doc'd
int spriteH(int i); // Doc'd
void replaceSprite(int s, const std::string& f, int w, int h, int m, int p, float x, float y);
void spriteSetBlendMode(int sprite, int blend); // Doc'd

} // namespace BruxAPI

#endif
