/*=============*\
| SPRITE HEADER |
\*=============*/

#ifndef _SPRITE_H_
#define _SPRITE_H_

class xySprite
{
private:
	Uint32 numero, mar, pad, w, h, tex, col, row, frames;
	bool didLoad;
	int osX, osY;
	float pvX, pvY;
	Uint32 *format;
public:
	string name;
	xySprite(const char* filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, int pivotX, int pivotY);
	~xySprite();
	void replaceSprite(const char* filename, Uint32 width, Uint32 height, Uint32 margin, Uint32 padding, int pivotX, int pivotY);
	void draw(int f, int x, int y);
	void drawex(int f, int x, int y, int angle, SDL_RendererFlip flip, float xscale, float yscale, float alpha);
	Uint32 getnum();
	Uint32 gettex();
	Uint32 getframes();
	Uint32 getw();
	Uint32 geth();
	const char* getname();
};

#endif
