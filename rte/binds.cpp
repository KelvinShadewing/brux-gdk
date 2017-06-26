/*===============*\
| BINDINGS SOURCE |
\*===============*/

#include "main.h"
#include "global.h"
#include "graphics.h"
#include "input.h"
#include "maths.h"
#include "fileio.h"
#include "text.h"
#include "binds.h"
#include "audio.h"

//////////
// MAIN //
//////////

int sqWait(HSQUIRRELVM v){
	SQInteger a;

	sq_getinteger(v, 2, &a);

	xyWait((int) a);

	return 0;
};

int sqUpdate(HSQUIRRELVM v){
	xyUpdate();

	return 0;
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

int sqGetTicks(HSQUIRRELVM v){
	sq_pushinteger(v, SDL_GetTicks());

	return 1;
};

int sqGetFPS(HSQUIRRELVM v){
	sq_pushinteger(v, gvFPS);

	return 1;
};

int sqSetFPS(HSQUIRRELVM v){
    int iMax;

    sq_getinteger(v, 2, &iMax);

    if(iMax < 0){
    	xyError(0, "Maximum FPS cannot be negative.");
		return 0;
    } else gvMaxFPS = iMax;

	return 0;
};

int sqSetWindowTitle(HSQUIRRELVM v){
	const char* t;

	sq_getstring(v, 2, &t);
	SDL_SetWindowTitle(gvWindow, t);

	return 0;
};

/////////////
// FILE IO //
/////////////

int sqImport(HSQUIRRELVM v){
	const char* a;

	sq_getstring(v, 2, &a);

	string b = gvAppDir;
	b += "xylib/";
	b += a;
	b += ".nut";

	sqstd_dofile(gvSquirrel, b.c_str(), 0, 1);

	return 0;
};

int sqFileExists(HSQUIRRELVM v){
	const char* file;

	sq_getstring(v, 2, &file);

	sq_pushbool(v, xyFileExists(file));

	return 1;
};

int sqGetDir(HSQUIRRELVM v){
	return 1;
};

int sqSetDir(HSQUIRRELVM v){
	return 0;
};

//////////////
// GRAPHICS //
//////////////

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
	Uint32 c;

	sq_getinteger(v, 2, (int*)&c);

	xySetDrawColor(c);

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

int sqSetResolution(HSQUIRRELVM v){
	int w, h;

	sq_getinteger(v, 2, &w);
	sq_getinteger(v, 3, &h);

	if(w < 1 || h < 1){
		xyError(0, "Window dimensions cannot be 0.");
		return 0;
	};

	SDL_Rect screensize;
	screensize.x = 0;
	screensize.y = 0;
	screensize.w = w;
	screensize.h = h;
	SDL_RenderSetViewport(gvRender, &screensize);
	SDL_RenderSetLogicalSize(gvRender, w, h);
	SDL_SetWindowSize(gvWindow, w, h);

	return 0;
};

/////////////
// SPRITES //
/////////////

int sqNewSprite(HSQUIRRELVM v){
	int w, h, m, p, px, py, f;
	const char* i;

	sq_getstring(v, 2, &i);
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

	if(vcSprites.size() <= i) return 0;
	if(vcSprites[i] == 0) return 0;

	vcSprites[i]->draw(f, x, y);

	return 0;
};

int sqDrawSpriteEx(HSQUIRRELVM v){
	int i, f, x, y, a, l;
	float sx, sy;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);
	sq_getinteger(v, 6, &a);
	sq_getinteger(v, 7, &l);
	sq_getfloat(v, 8, &sx);
	sq_getfloat(v, 9, &sy);

	if(vcSprites.size() <= i) return 0;
	if(vcSprites[i] == 0) return 0;

	vcSprites[i]->drawex(f, x, y, a, static_cast<SDL_RendererFlip>(l), sx, sy);

	return 0;
};

int sqDeleteSprite(HSQUIRRELVM v){
	int i;

	sq_getinteger(v, 2, &i);

	if(i >= vcSprites.size()) return 0;
	if(vcSprites[i] != 0) delete vcSprites[i];

	return 0;
};

///////////
// INPUT //
///////////

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

int sqMouseX(HSQUIRRELVM v){
	sq_pushinteger(v, gvMouseX);

	return 1;
};

int sqMouseY(HSQUIRRELVM v){
	sq_pushinteger(v, gvMouseY);

	return 1;
};

int sqMouseDown(HSQUIRRELVM v){
	int i;

	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, xyMouseButton(i));

	return 1;
};

int sqMousePress(HSQUIRRELVM v){
	int i;

	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, xyMousePress(i));

	return 1;
};

int sqMouseRelease(HSQUIRRELVM v){
	int i;

	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, xyMouseRelease(i));

	return 1;
};

int sqGetQuit(HSQUIRRELVM v){
	sq_pushbool(v, gvQuit);

	return 1;
};

///////////
// MATHS //
///////////

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

int sqDistance2(HSQUIRRELVM v){
	int x1, y1, x2, y2;

	sq_getinteger(v, 2, &x1);
	sq_getinteger(v, 3, &y1);
	sq_getinteger(v, 4, &x2);
	sq_getinteger(v, 5, &y2);

	sq_pushinteger(v, xyDistance(x1, y1, x2, y2));

	return 1;
};

int sqWrap(HSQUIRRELVM v){
	int x, mx, mn;

	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &mx);
	sq_getinteger(v, 4, &mn);

	sq_pushinteger(v, xyWrap(x, mn, mx));

	return 1;
};

int sqFloor(HSQUIRRELVM v){
	float f;

	sq_getfloat(v, 2, &f);
	sq_pushinteger(v, floor(f));

	return 1;
};

int sqPointAngle(HSQUIRRELVM v){
	float x1, y1, x2, y2;

	sq_getfloat(v, 2, &x1);
	sq_getfloat(v, 3, &y1);
	sq_getfloat(v, 4, &x2);
	sq_getfloat(v, 5, &y2);

	sq_pushfloat(v, xyPointAngle(x1, y1, x2, y2));

	return 1;
};

//////////
// TEXT //
//////////

int sqDrawText(HSQUIRRELVM v){
	float x, y;
	const char* t;
	int f, c, ha, va;

	sq_getfloat(v, 2, &x);
	sq_getfloat(v, 3, &y);
	sq_getstring(v, 4, &t);
	sq_getinteger(v, 5, &f);
	sq_getinteger(v, 6, &c);
	sq_getinteger(v, 7, &ha);
	sq_getinteger(v, 8, &va);

	xyDrawText(x, y, t, f, c, ha, va);

	return 0;
};

int sqOpenFont(HSQUIRRELVM v){
	const char* f;
	int s;

	sq_getstring(v, 2, &f);
	sq_getinteger(v, 3, &s);

	if(s < 1) s = 1;

	sq_pushinteger(v, xyOpenFont(f, s));

	return 1;
};

int sqCloseFont(HSQUIRRELVM v){
	int f;

	sq_getinteger(v, 2, &f);

	xyCloseFont(f);

	return 0;
};

///////////
// AUDIO //
///////////

int sqLoadSound(HSQUIRRELVM v){
	const char* s;

	sq_getstring(v, 2, &s);

	sq_pushinteger(v, xyLoadSound(s));

	return 1;
};

int sqLoadMusic(HSQUIRRELVM v){
	const char* m;

	sq_getstring(v, 2, &m);

	sq_pushinteger(v, xyLoadMusic(m));

	return 1;
};

int sqPlaySound(HSQUIRRELVM v){
	int s, l;

	sq_getinteger(v, 2, &s);
	sq_getinteger(v, 3, &l);

	sq_pushinteger(v, xyPlaySound(s, l));

	return 1;
};

int sqPlayMusic(HSQUIRRELVM v){
	int m, l;

	sq_getinteger(v, 2, &m);
	sq_getinteger(v, 3, &l);

	xyPlayMusic(m, l);

	return 0;
};

int sqDeleteSound(HSQUIRRELVM v){
	int i;

	sq_getinteger(v, 2, &i);

	xyDeleteSound(i);

	return 0;
};

int sqDeleteMusic(HSQUIRRELVM v){
	int i;

	sq_getinteger(v, 2, &i);

	xyDeleteMusic(i);

	return 0;
};


//////////
// MISC //
//////////

int sqEmbedTest(HSQUIRRELVM v){
	sq_pushinteger(v, 1);
	sq_pushinteger(v, 2);
	sq_pushinteger(v, 3);
	sq_pushinteger(v, 4);
	sq_pushinteger(v, 5);

	return 1;
};
