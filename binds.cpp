/*===============*\
| BINDINGS SOURCE |
\*===============*/

#include "main.h"
#include "global.h"
#include "graphics.h"
#include "input.h"
#include "maths.h"
#include "fileio.h"
#include "binds.h"



int sqWait(HSQUIRRELVM v){
	SQInteger a;

	sq_getinteger(v, 2, &a);

	xyWait((int) a);

	return 0;
};

int sqUpdateInput(HSQUIRRELVM v){
	xyUpdateInput();

	return 0;
};

int sqKeyPress(HSQUIRRELVM v){
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushinteger(v, xyKeyPress(a));

	return 1;
};

int sqKeyDown(HSQUIRRELVM v){
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushbool(v, xyKeyDown(a));

	return 1;
};

int sqKeyRelease(HSQUIRRELVM v){
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushbool(v, xyKeyRelease(a));

	return 1;
};

int sqClearScreen(HSQUIRRELVM v){
	SDL_RenderClear(gvRender);

	return 0;
};

int sqSetDrawTarget(HSQUIRRELVM v){
	SQInteger tex;

	sq_getinteger(v, 2, &tex);

	xySetDrawTarget(tex);

	return 0;
};

int sqResetDrawTarget(HSQUIRRELVM v){
	xyResetDrawTarget();

	return 0;
};

int sqDrawImage(HSQUIRRELVM v){
	int x, y, img;

	sq_getinteger(v, 2, &img);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);

	xyDrawImage(img, x, y);

	return 0;
};

int sqSetDrawColor(HSQUIRRELVM v){
	Uint8 r, g, b, a;

	sq_getinteger(v, 2, (int*)&r);
	sq_getinteger(v, 3, (int*)&g);
	sq_getinteger(v, 4, (int*)&b);
	sq_getinteger(v, 5, (int*)&a);

	xySetDrawColor(r, g, b, a);

	return 0;
};

int sqRandomFloat(HSQUIRRELVM v){
	float a;

	sq_getfloat(v, 2, &a);
	sq_pushinteger(v, xyRandomFloat(a));

	return 1;
};

int sqRandomInt(HSQUIRRELVM v){
	int a;

	sq_getinteger(v, 2, &a);
	sq_pushinteger(v, xyRandomInt(a));

	return 1;
};

int sqUpdateScreen(HSQUIRRELVM v){
	xyUpdateScreen();

	return 0;
};

int sqUpdate(HSQUIRRELVM v){
	xyUpdateScreen();
	xyUpdateInput();

	return 0;
};

int sqDrawRec(HSQUIRRELVM v){
	float x, y, w, h;
	Uint32 c;
	int o;

	sq_getfloat(v, 2, &x);
	sq_getfloat(v, 3, &y);
	sq_getfloat(v, 4, &w);
	sq_getfloat(v, 5, &h);
	sq_getinteger(v, 6, (int*)&c);
	if(sq_gettype(v, 7) == OT_INTEGER) sq_getinteger(v, 7, &o);
	else sq_getbool(v, 7, (unsigned int*)&o);

	xyDrawRec(x, y, w, h, c, o);

	return 0;
};

int sqLoadImage(HSQUIRRELVM v){
	const char* file;

	sq_getstring(v, 2, &file);

	sq_pushinteger(v, xyLoadImage(file));

	return 1;
};


int sqLoadImageKeyed(HSQUIRRELVM v){
	const char* file;
	int key;

	sq_getstring(v, 2, &file);
	sq_getinteger(v, 3, &key);

	sq_pushinteger(v, xyLoadImageKeyed(file, key));

	return 1;
};

int sqSetBackgroundColor(HSQUIRRELVM v){
	Uint32 color;

	sq_getinteger(v, 2, (int*)&color);

	xySetBackgroundColor(color);

	return 0;
};

int sqFileExists(HSQUIRRELVM v){
	const char* file;

	sq_getstring(v, 2, &file);

	sq_pushbool(v, xyFileExists(file));

	return 1;
};

int sqGetOS(HSQUIRRELVM v){
	switch(xyGetOS()){
		case 0:
			sq_pushstring(v, "windows", 7);
			break;
		case 1:
			sq_pushstring(v, "mac", 3);
			break;
		case 2:
			sq_pushstring(v, "linux", 5);
			break;
		case 3:
			sq_pushstring(v, "gcwz", 4);
			break;
		case 4:
			sq_pushstring(v, "pandora", 7);
			break;
		case 5:
			sq_pushstring(v, "android", 7);
			break;
		case 6:
			sq_pushstring(v, "ios", 7);
			break;
	};

	return 1;
};

int sqSetScalingFilter(HSQUIRRELVM v){
	int hint;

	sq_getinteger(v, 2, &hint);
	if(hint > 2) hint = 2;
	if(hint < 0) hint = 0;

	string strHint;
	strHint += "\"";
	strHint += hint;
	strHint += "\"";

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, strHint.c_str());

	return 0;
};

int sqNewSprite(HSQUIRRELVM v){
	int i, w, h, m, p, px, py, f;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &w);
	sq_getinteger(v, 4, &h);
	sq_getinteger(v, 5, &m);
	sq_getinteger(v, 6, &p);
	sq_getinteger(v, 7, &px);
	sq_getinteger(v, 8, &py);
	sq_getinteger(v, 9, &f);

	xySprite* newSprite = new xySprite(i, w, h, m, p, px, py, f);

	sq_pushinteger(v, newSprite->getnum());
	return 1;
};

int sqDrawSprite(HSQUIRRELVM v){
	int i, f, x, y;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);

	vcSprites[i]->draw(f, x, y);

	return 0;
};

int sqDrawSpriteEx(HSQUIRRELVM v){
	int i, f, x, y, a, l, sx, sy;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);
	sq_getinteger(v, 6, &a);
	sq_getinteger(v, 7, &l);
	sq_getinteger(v, 8, &sx);
	sq_getinteger(v, 9, &sy);

	vcSprites[i]->drawex(f, x, y, a, static_cast<SDL_RendererFlip>(l), sx, sy);

	return 0;
};


int sqMouseX(HSQUIRRELVM v){
	sq_pushinteger(v, gvMouseX);

	return 1;
};

int sqMouseY(HSQUIRRELVM v){
	sq_pushinteger(v, gvMouseY);

	return 1;
};