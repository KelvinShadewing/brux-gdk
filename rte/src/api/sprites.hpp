#ifndef BRUX_API_SPRITES_HEADER
#define BRUX_API_SPRITES_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Sprites
std::string spriteName(int sprite); // Doc'd
int findSprite(const std::string& name); // Doc'd
int newSprite(const std::string& i, int w, int h, int m, int p, int px, int py); // Doc'd
int newSpriteFT(int t, int w, int h, int m, int p, int px, int py);
void drawSprite(int i, float f, float x, float y); // Doc'd
void drawSpriteEx(int i, float f, float x, float y, float a, int l, float sx, float sy, float p); // Doc'd
void drawSpriteMod(int i, float f, float x, float y, float c); // Doc'd
void drawSpriteExMod(int i, float f, float x, float y, float a, int l, float sx, float sy, float p, float c); // Doc'd
void deleteSprite(int i); // Doc'd
int spriteW(int i); // Doc'd
int spriteH(int i); // Doc'd
void replaceSprite(int s, const std::string& f, int w, int h, int m, int p, int x, int y);
void spriteSetBlendMode(int sprite, int blend); // Doc'd

} // namespace BruxAPI

#endif
