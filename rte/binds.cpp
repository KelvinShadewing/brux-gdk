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
#include "audio.h"
#include "sprite.h"
#include "binds.h"

//////////
// MAIN //
//////////

SQInteger sqWait(HSQUIRRELVM v) {
	SQInteger a;

	sq_getinteger(v, 2, &a);

	xyWait((int) a);

	return 0;
};

SQInteger sqUpdate(HSQUIRRELVM v) {
	xyUpdate();

	return 0;
};

SQInteger sqGetOS(HSQUIRRELVM v) {
	const char* os = SDL_GetPlatform();

	sq_pushstring(v, os, -1);

	return 1;
};

SQInteger sqGetTicks(HSQUIRRELVM v) {
	sq_pushinteger(v, SDL_GetTicks());

	return 1;
};

SQInteger sqGetFPS(HSQUIRRELVM v) {
	sq_pushinteger(v, std::round(gvFPS));

	return 1;
};

SQInteger sqSetFPS(HSQUIRRELVM v) {
	SQInteger iMax;

	sq_getinteger(v, 2, &iMax);

	if(iMax < 0) {
		xyPrint(0, "Maximum FPS cannot be negative.");
		return 0;
	} else gvMaxFPS = iMax;

	return 0;
};

SQInteger sqSetWindowTitle(HSQUIRRELVM v) {
	const char* t;

	sq_getstring(v, 2, &t);
	SDL_SetWindowTitle(gvWindow, t);

	return 0;
};

SQInteger sqLoadWindowIcon(HSQUIRRELVM v) {
	const char* t;

	sq_getstring(v, 2, &t);
	if(xyFileExists(t)) {
		SDL_Surface* icon = IMG_Load(t);
		SDL_SetWindowIcon(gvWindow, icon);
		SDL_FreeSurface(icon);
	}

	return 0;
};

SQInteger sqGetFrames(HSQUIRRELVM v) {
	sq_pushinteger(v, gvFrames);
	return 1;
};

SQInteger sqGetDisplayH(HSQUIRRELVM v) {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	sq_pushinteger(v, DM.h);

	return 1;
};

SQInteger sqGetDisplayW(HSQUIRRELVM v) {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	sq_pushinteger(v, DM.w);

	return 1;
};

SQInteger sqBruxVersion(HSQUIRRELVM v) {
	sq_pushstring(v, gvVNo, strlen(gvVNo));
	return 1;
};

SQInteger sqToggleFullscreen(HSQUIRRELVM v) {
	SDL_SetWindowFullscreen(gvWindow, (SDL_GetWindowFlags(gvWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);

	return 0;
};



/////////////
// FILE IO //
/////////////

SQInteger sqImport(HSQUIRRELVM v) {
	//I don't remember why I have this function when sqDoNut() basically does the same thing
	const char* a;

	sq_getstring(v, 2, &a);

	std::string b = gvAppDir;
	b += "xylib/";
	b += a;
	b += ".nut";

	sqstd_dofile(gvSquirrel, b.c_str(), 0, 1);

	return 0;
};

SQInteger sqDoNut(HSQUIRRELVM v) {
	const char* a;

	sq_getstring(v, 2, &a);

	/*
	std::string b = "";
	char c[256];
	if(getcwd(c, sizeof(c)) == 0) return 0;
	b += c;
	b += "/";
	b += a;
	*/

	xyPrint(0, "Running %s...", a);
	sqstd_dofile(gvSquirrel, a, 0, 1);

	return 0;
};

SQInteger sqDoString(HSQUIRRELVM v) {
	const char* a;
	sq_getstring(v, 2, &a);

	SQInteger oldtop = sq_gettop(gvSquirrel);
	sq_compilebuffer(gvSquirrel, a, (int)strlen(a) * sizeof(SQChar), "std::string", 1);
	sq_pushroottable(gvSquirrel);
	sq_call(gvSquirrel, 1, SQFalse, SQTrue);
	sq_settop(gvSquirrel, oldtop);

	return 0;
}

SQInteger sqMount(HSQUIRRELVM v) {
	const char* dir;
	const char* mountpoint;
	SQBool prepend;

	sq_getstring(v, 2, &dir);
	sq_getstring(v, 3, &mountpoint);
	sq_getbool(v, 4, &prepend);

	xyFSMount(dir, mountpoint, prepend);

	return 0;
};

SQInteger sqUnmount(HSQUIRRELVM v) {
	const char* dir;

	sq_getstring(v, 2, &dir);

	xyFSUnmount(dir);

	return 0;
};

SQInteger sqGetDir(HSQUIRRELVM v) {
	const std::string data = xyGetDir();

	sq_pushstring(v, data.c_str(), data.size());

	return 1;
};

SQInteger sqGetWriteDir(HSQUIRRELVM v) {
	const std::string data = xyGetWriteDir();

	sq_pushstring(v, data.c_str(), data.size());

	return 1;
};

SQInteger sqGetPrefDir(HSQUIRRELVM v) {
	const char* org;
	const char* app;

	sq_getstring(v, 2, &org);
	sq_getstring(v, 3, &app);

	const std::string data = xyGetPrefDir(org, app);

	sq_pushstring(v, data.c_str(), data.size());

	return 1;
};

SQInteger sqSetWriteDir(HSQUIRRELVM v) {
	const char* dir;

	sq_getstring(v, 2, &dir);

	xySetWriteDir(dir);

	return 0;
};

SQInteger sqCreateDir(HSQUIRRELVM v) {
	const char* name;

	sq_getstring(v, 2, &name);

	xyCreateDir(name);

	return 0;
};

SQInteger sqFileRead(HSQUIRRELVM v) {
	const char* file;

	sq_getstring(v, 2, &file);

	if (xyFileExists(file)) {
		const std::string data = xyFileRead(file);
		sq_pushstring(v, data.c_str(), data.size());
	}
	else {
		xyPrint(0, "WARNING: %s does not exist!", file);
		sq_pushstring(v, "-1", 2);
	}
	return 1;
};

SQInteger sqFileWrite(HSQUIRRELVM v) {
	const char* file;
	const char* data;

	sq_getstring(v, 2, &file);
	sq_getstring(v, 3, &data);

	xyFileWrite(file, data);

	return 0;
};

SQInteger sqFileAppend(HSQUIRRELVM v) {
	const char* file;
	const char* data;

	sq_getstring(v, 2, &file);
	sq_getstring(v, 3, &data);

	xyFileAppend(file, data);

	return 0;
};

SQInteger sqFileExists(HSQUIRRELVM v) {
	const char* file;

	sq_getstring(v, 2, &file);

	sq_pushbool(v, xyFileExists(file));

	return 1;
};

SQInteger sqFileDelete(HSQUIRRELVM v) {
	const char* file;

	sq_getstring(v, 2, &file);

	xyFileDelete(file);

	return 0;
};

SQInteger sqIsDir(HSQUIRRELVM v) {
	const char* dir;

	sq_getstring(v, 2, &dir);

	sq_pushbool(v, xyIsDirectory(dir));

	return 1;
};

SQInteger sqLsDir(HSQUIRRELVM v) {
	const char* dir;

	sq_getstring(v, 2, &dir);

	// Create array for results.
	sq_newarray(v, 0);

	// Append all results to the array.
	const std::vector<std::string> files = xyListDirectory(dir);
	for (const std::string& file : files) {
		sq_pushstring(v, file.c_str(), file.size());
		sq_arrayappend(v, -2);
	}

	return 1;
};



//////////////
// GRAPHICS //
//////////////

SQInteger sqClearScreen(HSQUIRRELVM v) {
	SDL_RenderClear(gvRender);

	return 0;
};

SQInteger sqSetDrawTarget(HSQUIRRELVM v) {
	SQInteger tex;

	sq_getinteger(v, 2, &tex);

	xySetDrawTarget(tex);
	gvDrawTarget = tex;

	return 0;
};

SQInteger sqGetDrawTarget(HSQUIRRELVM v) {
	sq_pushinteger(v, gvDrawTarget);

	return 1;
};

SQInteger sqResetDrawTarget(HSQUIRRELVM v) {
	xyResetDrawTarget();

	return 0;
};

SQInteger sqDrawImage(HSQUIRRELVM v) {
	SQInteger x, y, img;

	sq_getinteger(v, 2, &img);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);

	xyDrawImage(img, x, y);

	return 0;
};

SQInteger sqDrawImageEx(HSQUIRRELVM v) {
	SQInteger x, y, img, f, c;
	SQFloat a, w, h, r;

	sq_getinteger(v, 2, &img);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);
	sq_getfloat(v, 5, &a);
	sq_getinteger(v, 6, &f);
	sq_getfloat(v, 7, &w);
	sq_getfloat(v, 8, &h);
	sq_getinteger(v, 9, &c);

	xyDrawImageEx(img, x, y, a, static_cast<SDL_RendererFlip>(f), w, h, r, c);

	return 0;
};

SQInteger sqSetDrawColor(HSQUIRRELVM v) {
	SQInteger c;

	sq_getinteger(v, 2, &c);

	xySetDrawColor(c);

	return 0;
};

SQInteger sqLoadImage(HSQUIRRELVM v) {
	const char* file;

	sq_getstring(v, 2, &file);

	sq_pushinteger(v, xyLoadImage(file));

	return 1;
};

SQInteger sqLoadImageKeyed(HSQUIRRELVM v) {
	const char* file;
	SQInteger key;

	sq_getstring(v, 2, &file);
	sq_getinteger(v, 3, &key);

	sq_pushinteger(v, xyLoadImageKeyed(file, key));

	return 1;
};

SQInteger sqSetBackgroundColor(HSQUIRRELVM v) {
	SQInteger color;

	sq_getinteger(v, 2, &color);

	xySetBackgroundColor(color);

	return 0;
};

SQInteger sqSetScaling(HSQUIRRELVM v) {
	SQFloat scale;

	sq_getfloat(v, 2, &scale);

	if(scale > 0) SDL_RenderSetScale(gvRender, scale, scale);

	return 0;
};

SQInteger sqSetScalingFilter(HSQUIRRELVM v) {
	SQInteger hint;

	sq_getinteger(v, 2, &hint);
	if(hint > 2) hint = 2;
	if(hint < 0) hint = 0;

	std::string strHint;
	switch(hint) {
		case 0:
			strHint = "0";
			break;
		case 1:
			strHint = "1";
			break;
		case 2:
			strHint = "2";
			break;
		default:
			strHint = "0";
			break;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, strHint.c_str());

	return 0;
};

SQInteger sqSetResolution(HSQUIRRELVM v) {
	SQInteger w, h;

	sq_getinteger(v, 2, &w);
	sq_getinteger(v, 3, &h);

	if(w < 1 || h < 1) {
		xyPrint(0, "Window dimensions cannot be 0.");
		return 0;
	}

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

SQInteger sqGetScreenW(HSQUIRRELVM v) {
	SDL_Rect vp;
	SDL_RenderGetViewport(gvRender, &vp);
	sq_pushinteger(v, vp.w);
	return 1;
}

SQInteger sqGetScreenH(HSQUIRRELVM v) {
	SDL_Rect vp;
	SDL_RenderGetViewport(gvRender, &vp);
	sq_pushinteger(v, vp.h);
	return 1;
}

SQInteger sqGetWindowW(HSQUIRRELVM v) {
	int w;

	SDL_GetWindowSize(gvWindow, &w, 0);
	sq_pushinteger(v, w);

	return 1;
}

SQInteger sqGetWindowH(HSQUIRRELVM v) {
	int h;

	SDL_GetWindowSize(gvWindow, 0, &h);
	sq_pushinteger(v, h);

	return 1;
}

SQInteger sqNewTexture(HSQUIRRELVM v) {
	SQInteger w, h;

	sq_getinteger(v, 2, &w);
	sq_getinteger(v, 3, &h);

	SQInteger t = xyNewTexture(w, h);

	sq_pushinteger(v, t);
	return 1;
};

SQInteger sqTextureSetBlendMode(HSQUIRRELVM v) {
	SQInteger t, b;
	SDL_BlendMode m;

	sq_getinteger(v, 2, &t);
	sq_getinteger(v, 3, &b);

	if(t < 0) {
		xyPrint(0, "Invalid texture ID. Cannot set blend mode.");
		return 0;
	};

	if(t > vcTextures.size() - 1) {
		xyPrint(0, "Invalid texture ID. Cannot set blend mode.");
		return 0;
	};

	switch(b) {
		case 0:
			m = SDL_BLENDMODE_NONE;
			break;
		case 1:
			m = SDL_BLENDMODE_BLEND;
			break;
		case 2:
			m = SDL_BLENDMODE_ADD;
			break;
		case 3:
			m = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT, SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT);
			break;
		case 4:
			m = SDL_BLENDMODE_MOD;
			break;
		default:
			m = SDL_BLENDMODE_NONE;
			break;
	};

	SDL_SetTextureBlendMode(vcTextures[t], m);

	return 0;
};



/////////////
// SPRITES //
/////////////

SQInteger sqSpriteName(HSQUIRRELVM v) {
	SQInteger s;

	sq_getinteger(v, 2, &s);

	if(vcSprites.size() <= s || s < 0) sq_pushstring(v, "N/A", 3);
	else if(vcSprites[s] == 0) sq_pushstring(v, "N/A", 3);
	else sq_pushstring(v, vcSprites[s]->name.c_str(), vcSprites[s]->name.length());

	return 1;
};

SQInteger sqFindSprite(HSQUIRRELVM v) {
	const char* n;
	sq_getstring(v, 2, &n);
	std::string nn = n;
	//Print(0, "Searching for sprite: %s", n);
	//xyPrint(0, "Number of sprites to search: %i", vcSprites.size());

	for(size_t i = 0; i < vcSprites.size(); i++) {
		if(vcSprites[i] != 0) {
			//xyPrint(0, "Current sprite name: %s", vcSprites[i]->getname());

			if(vcSprites[i]->getname() == nn) {
				sq_pushinteger(v, vcSprites[i]->getnum());
				return 1;
				break;
			}
		}
	}

	sq_pushinteger(v, 0);
	return 1;
};

SQInteger sqNewSprite(HSQUIRRELVM v) {
	SQInteger w, h, m, p, px, py;
	const char* i;

	sq_getstring(v, 2, &i);
	sq_getinteger(v, 3, &w);
	sq_getinteger(v, 4, &h);
	sq_getinteger(v, 5, &m);
	sq_getinteger(v, 6, &p);
	sq_getinteger(v, 7, &px);
	sq_getinteger(v, 8, &py);

	xySprite* newSprite = new xySprite(i, w, h, m, p, px, py);

	sq_pushinteger(v, newSprite->getnum());
	return 1;
};

SQInteger sqNewSpriteFT(HSQUIRRELVM v) {
	SQInteger t, w, h, m, p, px, py;

	sq_getinteger(v, 2, &t);
	sq_getinteger(v, 3, &w);
	sq_getinteger(v, 4, &h);
	sq_getinteger(v, 5, &m);
	sq_getinteger(v, 6, &p);
	sq_getinteger(v, 7, &px);
	sq_getinteger(v, 8, &py);

	xySprite* newSprite = new xySprite(t, w, h, m, p, px, py);

	sq_pushinteger(v, newSprite->getnum());
	return 1;
};

SQInteger sqDrawSprite(HSQUIRRELVM v) {
	SQInteger i, f, x, y;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);

	if(vcSprites.size() <= i) return 0;
	if(vcSprites[i] == 0) return 0;

	vcSprites[i]->draw(f, x, y);

	return 0;
};

SQInteger sqDrawSpriteEx(HSQUIRRELVM v) {
	SQInteger i, f, x, y, a, l;
	float sx, sy, p;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);
	sq_getinteger(v, 6, &a);
	sq_getinteger(v, 7, &l);
	sq_getfloat(v, 8, &sx);
	sq_getfloat(v, 9, &sy);
	sq_getfloat(v, 10, &p);

	if(vcSprites.size() <= i) return 0;
	if(vcSprites[i] == 0) return 0;

	vcSprites[i]->drawex(f, x, y, a, static_cast<SDL_RendererFlip>(l), sx, sy, p);

	return 0;
};

SQInteger sqDrawSpriteMod(HSQUIRRELVM v) {
	SQInteger i, f, x, y, c;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);
	sq_getinteger(v, 6, &c);

	if(vcSprites.size() <= i) return 0;
	if(vcSprites[i] == 0) return 0;

	vcSprites[i]->drawmod(f, x, y, c);

	return 0;
};

SQInteger sqDrawSpriteExMod(HSQUIRRELVM v) {
	SQInteger i, f, x, y, a, l, c;
	float sx, sy, p;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &f);
	sq_getinteger(v, 4, &x);
	sq_getinteger(v, 5, &y);
	sq_getinteger(v, 6, &a);
	sq_getinteger(v, 7, &l);
	sq_getfloat(v, 8, &sx);
	sq_getfloat(v, 9, &sy);
	sq_getfloat(v, 10, &p);
	sq_getinteger(v, 11, &c);

	if(vcSprites.size() <= i) return 0;
	if(vcSprites[i] == 0) return 0;

	vcSprites[i]->drawexmod(f, x, y, a, static_cast<SDL_RendererFlip>(l), sx, sy, p, c);

	return 0;
};

SQInteger sqDeleteSprite(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	if(i >= vcSprites.size()) return 0;
	if(vcSprites[i] != 0) delete vcSprites[i];

	return 0;
};

SQInteger sqSpriteW(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	if(i >= vcSprites.size()) return 0;
	if(vcSprites[i] != 0) sq_pushinteger(v, vcSprites[i]->getw());
	else sq_pushinteger(v, 0);

	return 1;
};

SQInteger sqSpriteH(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	if(i >= vcSprites.size()) return 0;
	if(vcSprites[i] != 0) sq_pushinteger(v, vcSprites[i]->geth());
	else sq_pushinteger(v, 0);

	return 1;
};

SQInteger sqReplaceSprite(HSQUIRRELVM v) {
	const char* f;
	SQInteger s, w, h, m, p, x, y;

	sq_getinteger(v, 2, &s);
	sq_getstring(v, 3, &f);
	sq_getinteger(v, 4, &w);
	sq_getinteger(v, 5, &h);
	sq_getinteger(v, 6, &m);
	sq_getinteger(v, 7, &p);
	sq_getinteger(v, 8, &x);
	sq_getinteger(v, 9, &y);

	if(s > 0 && s < vcSprites.size()) {
		if(vcSprites[s] != 0) vcSprites[s]->replaceSprite(f, w, h, m, p, x, y);
		else vcSprites[s] = new xySprite(f, w, h, m, p, x, y);
	}

	return 0;
};

SQInteger sqSpriteSetBlendMode(HSQUIRRELVM v) {
	SQInteger t, s, b;
	SDL_BlendMode m;

	sq_getinteger(v, 2, &s);
	sq_getinteger(v, 3, &b);

	if(s < 0) {
		xyPrint(0, "Invalid sprite ID. Cannot set blend mode.");
		return 0;
	};

	if(s > vcSprites.size() - 1) {
		xyPrint(0, "Invalid sprite ID. Cannot set blend mode.");
		return 0;
	};

	t = vcSprites[s]->gettex();

	switch(b) {
		case 0:
			m = SDL_BLENDMODE_NONE;
			break;
		case 1:
			m = SDL_BLENDMODE_BLEND;
			break;
		case 2:
			m = SDL_BLENDMODE_ADD;
			break;
		case 3:
			m = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT, SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_SUBTRACT);
			break;
		case 4:
			m = SDL_BLENDMODE_MOD;
			break;
		default:
			m = SDL_BLENDMODE_NONE;
			break;
	};

	SDL_SetTextureBlendMode(vcTextures[t], m);

	return 0;
};



///////////
// INPUT //
///////////

SQInteger sqKeyPress(HSQUIRRELVM v) {
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushinteger(v, xyKeyPress(a));

	return 1;
};

SQInteger sqKeyDown(HSQUIRRELVM v) {
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushbool(v, xyKeyDown(a));

	return 1;
};

SQInteger sqKeyRelease(HSQUIRRELVM v) {
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushbool(v, xyKeyRelease(a));

	return 1;
};

SQInteger sqKeyPressAny(HSQUIRRELVM v) {
	SQInteger a = -1;

	for(int i = 0; i < 322; i++) {
		if(xyKeyPress(i)) {
			a = i;
			break;
		}
	}

	sq_pushinteger(v, a);
	return 1;
};

SQInteger sqMouseDown(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, xyMouseButton(i));

	return 1;
};

SQInteger sqMousePress(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, xyMousePress(i));

	return 1;
};

SQInteger sqMouseRelease(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, xyMouseRelease(i));

	return 1;
};

SQInteger sqMouseX(HSQUIRRELVM v) {
	sq_pushinteger(v, gvMouseX);
	return 1;
};

SQInteger sqMouseY(HSQUIRRELVM v) {
	sq_pushinteger(v, gvMouseY);
	return 1;
};

SQInteger sqGetQuit(HSQUIRRELVM v) {
	sq_pushbool(v, gvQuit);

	return 1;
};

SQInteger sqGetPads(HSQUIRRELVM v) {
	sq_pushinteger(v, SDL_NumJoysticks());

	return 1;
};

SQInteger sqPadName(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushstring(v, gvPadName[i].c_str(), gvPadName[i].length());

	return 1;
};

SQInteger sqPadX(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadX[i]);

	return 1;
};

SQInteger sqPadY(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadY[i]);

	return 1;
};

SQInteger sqPadZ(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadZ[i]);

	return 1;
};

SQInteger sqPadH(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadH[i]);

	return 1;
};

SQInteger sqPadV(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadV[i]);

	return 1;
};

SQInteger sqPadR(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadR[i]);

	return 1;
};

SQInteger sqPadL(HSQUIRRELVM v) {
	SQInteger i;
	sq_getinteger(v, 2, &i);

	sq_pushinteger(v, gvPadL[i]);

	return 1;
};

SQInteger sqPadAxis(HSQUIRRELVM v) {
	SQInteger i, j;
	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &j);

	sq_pushinteger(v, gvPadAxis[i][j]);

	return 1;
};

SQInteger sqPadHatDown(HSQUIRRELVM v) {
	SQInteger i, d;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &d);

	if (gvPadHat[i] & (1 << (d - 1))) sq_pushbool(v, true);
	else sq_pushbool(v, false);

	return 1;
};

SQInteger sqPadHatPress(HSQUIRRELVM v) {
	SQInteger i, d;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &d);

	if ((gvPadHat[i] & (1 << (d - 1))) && !(gvPadHatLast[i] & (1 << (d - 1)))) sq_pushbool(v, true);
	else sq_pushbool(v, false);

	return 1;
};

SQInteger sqPadHatRelease(HSQUIRRELVM v) {
	SQInteger i, d;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &d);

	if (!(gvPadHat[i] & (1 << (d - 1))) && (gvPadHatLast[i] & (1 << (d - 1)))) sq_pushbool(v, true);
	else sq_pushbool(v, false);

	return 1;
};

SQInteger sqPadButtonDown(HSQUIRRELVM v) {
	SQInteger i, b;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &b);

	sq_pushinteger(v, gvPadButton[i][b]);

	return 1;
};

SQInteger sqPadButtonPress(HSQUIRRELVM v) {
	SQInteger i, b;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &b);

	sq_pushinteger(v, (gvPadButton[i][b] && !gvPadLastButton[i][b]) );

	return 1;
};

SQInteger sqPadButtonAny(HSQUIRRELVM v) {
	int a = -1;
	SQInteger p;

	sq_getinteger(v, 2, &p);

	for(int i = 0; i < 32; i++) {
		if(gvPadButton[p][i] && !gvPadLastButton[p][i]) {
			a = i;
			break;
		}
	}

	sq_pushinteger(v, a);

	return 1;
};

SQInteger sqPadButtonRelease(HSQUIRRELVM v) {
	SQInteger i, b;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &b);

	sq_pushinteger(v, (!gvPadButton[i][b] && gvPadLastButton[i][b]) );

	return 1;
};

SQInteger sqPadAxisPress(HSQUIRRELVM v) {
	SQInteger p, a, d;

	sq_getinteger(v, 2, &p);
	sq_getinteger(v, 3, &a);
	sq_getinteger(v, 4, &d);

	sq_pushinteger(v, xyJoyAxisPress(p, a, d));

	return 1;
};

SQInteger sqPadAxisRelease(HSQUIRRELVM v) {
	SQInteger p, a, d;

	sq_getinteger(v, 2, &p);
	sq_getinteger(v, 3, &a);
	sq_getinteger(v, 4, &d);

	sq_pushinteger(v, xyJoyAxisRelease(p, a, d));

	return 1;
};

SQInteger sqKeyChar(HSQUIRRELVM v) {
	sq_pushstring(v, gvInputString.c_str(), gvInputString.length());
	gvInputString = ""; //Clean input

	return 1;
}

SQInteger sqMouseWheelX(HSQUIRRELVM v) {
	sq_pushinteger(v, mouseWheelX);

	return 1;
}

SQInteger sqMouseWheelY(HSQUIRRELVM v) {
	sq_pushinteger(v, mouseWheelY);

	return 1;
}



///////////
// MATHS //
///////////

SQInteger sqRandomFloat(HSQUIRRELVM v) {
	float a;

	sq_getfloat(v, 2, &a);
	sq_pushfloat(v, xyRandomFloat(a));

	return 1;
};

SQInteger sqRandomInt(HSQUIRRELVM v) {
	SQInteger a;

	sq_getinteger(v, 2, &a);
	sq_pushinteger(v, xyRandomInt(a));

	return 1;
};

SQInteger sqDistance2(HSQUIRRELVM v) {
	SQFloat x1, y1, x2, y2;

	sq_getfloat(v, 2, &x1);
	sq_getfloat(v, 3, &y1);
	sq_getfloat(v, 4, &x2);
	sq_getfloat(v, 5, &y2);

	sq_pushfloat(v, xyDistance(x1, y1, x2, y2));

	return 1;
};

SQInteger sqInDistance2(HSQUIRRELVM v) {
	SQFloat x1, y1, x2, y2, d;

	sq_getfloat(v, 2, &x1);
	sq_getfloat(v, 3, &y1);
	sq_getfloat(v, 4, &x2);
	sq_getfloat(v, 5, &y2);
	sq_getfloat(v, 6, &d);

	sq_pushbool(v, xyInDistance2(x1, y1, x2, y2, d));

	return 1;
};

SQInteger sqDistance3(HSQUIRRELVM v) {
	SQFloat x1, y1, z1, x2, y2, z2;

	sq_getfloat(v, 2, &x1);
	sq_getfloat(v, 3, &y1);
	sq_getfloat(v, 4, &z1);
	sq_getfloat(v, 5, &x2);
	sq_getfloat(v, 6, &y2);
	sq_getfloat(v, 7, &z2);

	sq_pushfloat(v, xyDistance3(x1, y1, z1, x2, y2, z2));

	return 1;
};

SQInteger sqWrap(HSQUIRRELVM v) {
	SQFloat x, mx, mn;

	sq_getfloat(v, 2, &x);
	sq_getfloat(v, 3, &mx);
	sq_getfloat(v, 4, &mn);

	sq_pushfloat(v, xyWrap(x, mn, mx));

	return 1;
};

SQInteger sqFloor(HSQUIRRELVM v) {
	float f;

	sq_getfloat(v, 2, &f);
	sq_pushinteger(v, floor(f));

	return 1;
};

SQInteger sqCeil(HSQUIRRELVM v) {
	float f;

	sq_getfloat(v, 2, &f);
	sq_pushinteger(v, ceil(f));

	return 1;
};

SQInteger sqRound(HSQUIRRELVM v) {
	float f;

	sq_getfloat(v, 2, &f);
	sq_pushinteger(v, round(f));

	return 1;
};

SQInteger sqPointAngle(HSQUIRRELVM v) {
	float x1, y1, x2, y2;

	sq_getfloat(v, 2, &x1);
	sq_getfloat(v, 3, &y1);
	sq_getfloat(v, 4, &x2);
	sq_getfloat(v, 5, &y2);

	sq_pushfloat(v, xyPointAngle(x1, y1, x2, y2));

	return 1;
};

SQInteger sqAbs(HSQUIRRELVM v) {
	float f;

	sq_getfloat(v, 2, &f);
	sq_pushfloat(v, abs(f));

	return 1;
};

SQInteger sqLenDirX(HSQUIRRELVM v) {
	float l, d;

	sq_getfloat(v, 2, &l);
	sq_getfloat(v, 3, &d);
	sq_pushfloat(v, xyLenDirX(l, d));

	return 1;
};

SQInteger sqLenDirY(HSQUIRRELVM v) {
	float l, d;

	sq_getfloat(v, 2, &l);
	sq_getfloat(v, 3, &d);
	sq_pushfloat(v, xyLenDirY(l, d));

	return 1;
};

SQInteger sqBinStr(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	int l = (int)log2(i) + 1;
	std::string s;

	switch(l) {
		case 0:
			s = "0";
			break;
		case 1:
			s = std::bitset<1>(i).to_string();
			break;
		case 2:
			s = std::bitset<2>(i).to_string();
			break;
		case 3:
			s = std::bitset<3>(i).to_string();
			break;
		case 4:
			s = std::bitset<4>(i).to_string();
			break;
		case 5:
			s = std::bitset<5>(i).to_string();
			break;
		case 6:
			s = std::bitset<6>(i).to_string();
			break;
		case 7:
			s = std::bitset<7>(i).to_string();
			break;
		case 8:
			s = std::bitset<8>(i).to_string();
			break;
		case 9:
			s = std::bitset<9>(i).to_string();
			break;
		case 10:
			s = std::bitset<10>(i).to_string();
			break;
		case 11:
			s = std::bitset<11>(i).to_string();
			break;
		case 12:
			s = std::bitset<12>(i).to_string();
			break;
		case 13:
			s = std::bitset<13>(i).to_string();
			break;
		case 14:
			s = std::bitset<14>(i).to_string();
			break;
		case 15:
			s = std::bitset<15>(i).to_string();
			break;
		case 16:
			s = std::bitset<16>(i).to_string();
			break;
		case 17:
			s = std::bitset<17>(i).to_string();
			break;
		case 18:
			s = std::bitset<18>(i).to_string();
			break;
		case 19:
			s = std::bitset<19>(i).to_string();
			break;
		case 20:
			s = std::bitset<20>(i).to_string();
			break;
		case 21:
			s = std::bitset<21>(i).to_string();
			break;
		case 22:
			s = std::bitset<22>(i).to_string();
			break;
		case 23:
			s = std::bitset<23>(i).to_string();
			break;
		case 24:
			s = std::bitset<24>(i).to_string();
			break;
		case 25:
			s = std::bitset<25>(i).to_string();
			break;
		case 26:
			s = std::bitset<26>(i).to_string();
			break;
		case 27:
			s = std::bitset<27>(i).to_string();
			break;
		case 28:
			s = std::bitset<28>(i).to_string();
			break;
		case 29:
			s = std::bitset<29>(i).to_string();
			break;
		case 30:
			s = std::bitset<30>(i).to_string();
			break;
		case 31:
			s = std::bitset<31>(i).to_string();
			break;
		case 32:
			s = std::bitset<32>(i).to_string();
			break;
		default:
			s = std::bitset<64>(i).to_string();
			break;
	}

	sq_pushstring(v, s.c_str(), -1);

	return 1;
};



//////////
// TEXT //
//////////

SQInteger sqNewFont(HSQUIRRELVM v) {
	SQInteger i, c, t, k;
	SQBool m;

	sq_getinteger(v, 2, &i);
	sq_getinteger(v, 3, &c);
	sq_getinteger(v, 4, &t);
	sq_getbool(v, 5, &m);
	sq_getinteger(v, 6, &k);

	//Sanitize inputs
	if(i < 0) i = 0;
	if(t > 255) t = 255;
	if(c > 255) c = 255;

	xyFont* newfont = new xyFont(i, (char)c, t, m, k);

	sq_pushinteger(v, newfont->getnum());

	return 1;
};

SQInteger sqDrawText(HSQUIRRELVM v) {
	SQInteger f, x, y;
	const char* s;

	sq_getinteger(v, 2, &f);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);
	sq_getstring(v, 5, &s);

	if(f >= vcFonts.size()) return 0;
	if(vcFonts[f] == 0) return 0;

	vcFonts[f]->draw(x, y, s);

	return 0;
};

SQInteger sqChint(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	const char s = (const char)i;

	sq_pushstring(v, &s, 1);

	return 1;
}



///////////
// AUDIO //
///////////

SQInteger sqLoadSound(HSQUIRRELVM v) {
	const char* s;

	sq_getstring(v, 2, &s);

	sq_pushinteger(v, xyLoadSound(s));

	return 1;
};

SQInteger sqLoadMusic(HSQUIRRELVM v) {
	const char* m;

	sq_getstring(v, 2, &m);

	sq_pushinteger(v, xyLoadMusic(m));

	return 1;
};

SQInteger sqPlaySound(HSQUIRRELVM v) {
	SQInteger s, l;

	sq_getinteger(v, 2, &s);
	sq_getinteger(v, 3, &l);

	SQInteger ret = xyPlaySound(s, l);
	if(ret != -1) Mix_Volume(ret, gvVolumeSound);
	sq_pushinteger(v, ret);

	return 1;
};

SQInteger sqPlaySoundChannel(HSQUIRRELVM v){
	SQInteger s, l, c;

	sq_getinteger(v, 2, &s);
	sq_getinteger(v, 3, &l);
	sq_getinteger(v, 4, &c);

	int i = Mix_PlayChannel(c, vcSounds[s], l);
	if(i == -1) xyPrint(0, "Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
	else Mix_Volume(i, gvVolumeSound);
	sq_pushinteger(v, i);

	return 1;
};

SQInteger sqPlayMusic(HSQUIRRELVM v) {
	SQInteger m, l;

	sq_getinteger(v, 2, &m);
	sq_getinteger(v, 3, &l);

	xyPlayMusic(m, l);
	Mix_VolumeMusic(gvVolumeMusic);

	return 0;
};

SQInteger sqDeleteSound(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	xyDeleteSound(i);

	return 0;
};

SQInteger sqDeleteMusic(HSQUIRRELVM v) {
	SQInteger i;

	sq_getinteger(v, 2, &i);

	xyDeleteMusic(i);

	return 0;
};

SQInteger sqStopSound(HSQUIRRELVM v) {
	SQInteger c;

	sq_getinteger(v, 2, &c);

	xyStopSound(c);

	return 0;
};

SQInteger sqStopChannel(HSQUIRRELVM v) {
	SQInteger c;

	sq_getinteger(v, 2, &c);

	Mix_HaltChannel(c);

	return 0;
};

SQInteger sqStopMusic(HSQUIRRELVM v) {
	Mix_HaltMusic();
	return 0;
};

SQInteger sqCheckMusic(HSQUIRRELVM v) {
	bool b = Mix_PlayingMusic();
	sq_pushbool(v, b);
	return 1;
};

SQInteger sqCheckSound(HSQUIRRELVM v) {
	bool b;
	SQInteger c;
	sq_getinteger(v, 2, &c);
	b = Mix_Playing(c);
	sq_pushbool(v, b);
	return 1;
};

SQInteger sqSetMaxChannels(HSQUIRRELVM v) {
	SQInteger c;
	sq_getinteger(v, 2, &c);
	Mix_AllocateChannels(c);
	return 0;
};

SQInteger sqPauseMusic(HSQUIRRELVM v) {
	Mix_PauseMusic();
	return 0;
};

SQInteger sqResumeMusic(HSQUIRRELVM v) {
	Mix_ResumeMusic();
	return 0;
};

SQInteger sqMusicPaused(HSQUIRRELVM v) {
	bool b;
	if(Mix_PlayingMusic()) b = Mix_PausedMusic();
	else b = false;
	sq_pushbool(v, b);
	return 1;
};

SQInteger sqFadeMusic(HSQUIRRELVM v) {
	SQFloat f;

	sq_getfloat(v, 2, &f);

	Mix_FadeOutMusic(f * 1000.0);

	return 1;
};

SQInteger sqSetMusicVolume(HSQUIRRELVM v) {
	SQInteger vol;

	sq_getinteger(v, 2, &vol);
	gvVolumeMusic = vol;
	Mix_VolumeMusic(vol);

	return 0;
};

SQInteger sqSetSoundVolume(HSQUIRRELVM v) {
	SQInteger vol;

	sq_getinteger(v, 2, &vol);
	gvVolumeSound = vol;

	return 0;
};

SQInteger sqGetMusicVolume(HSQUIRRELVM v) {
	sq_pushinteger(v, gvVolumeMusic);
	return 1;
};

SQInteger sqGetSoundVolume(HSQUIRRELVM v) {
	sq_pushinteger(v, gvVolumeSound);
	return 1;
};



/////////////
// SDL_GFX //
/////////////

SQInteger sqDrawCircle(HSQUIRRELVM v) {
	SQInteger x, y, r;
	SQBool f;

	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &r);
	sq_getbool(v, 5, &f);

	if(f) filledCircleColor(gvRender, x, y, r, gvDrawColor);
	else circleColor(gvRender, x, y, r, gvDrawColor);

	return 0;
};

SQInteger sqDrawRect(HSQUIRRELVM v) {
	SQInteger x, y, w, h;
	SQBool f;

	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &w);
	sq_getinteger(v, 5, &h);
	sq_getbool(v, 6, &f);

	if(f) boxColor(gvRender, x, y, x + w, y + h, gvDrawColor);
	else rectangleColor(gvRender, x, y, x + w, y + h, gvDrawColor);

	return 0;
};

SQInteger sqDrawPoint(HSQUIRRELVM v) {
	SQInteger x, y;

	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);

	pixelColor(gvRender, x, y, gvDrawColor);

	return 0;
};

SQInteger sqDrawLine(HSQUIRRELVM v) {
	SQInteger x1, y1, x2, y2;

	sq_getinteger(v, 2, &x1);
	sq_getinteger(v, 3, &y1);
	sq_getinteger(v, 4, &x2);
	sq_getinteger(v, 5, &y2);

	thickLineColor(gvRender, x1, y1, x2, y2, 1, gvDrawColor);

	return 0;
};

SQInteger sqDrawLineWide(HSQUIRRELVM v) {
	SQInteger x1, y1, x2, y2, w;

	sq_getinteger(v, 2, &x1);
	sq_getinteger(v, 3, &y1);
	sq_getinteger(v, 4, &x2);
	sq_getinteger(v, 5, &y2);
	sq_getinteger(v, 6, &w);

	thickLineColor(gvRender, x1, y1, x2, y2, w, gvDrawColor);

	return 0;
};



////////////
// SHAPES //
////////////

SQInteger sqLineLine(HSQUIRRELVM v) {
	SQFloat x0, y0, x1, y1, x2, y2, x3, y3;

	sq_getfloat(v, 2, &x0);
	sq_getfloat(v, 3, &y0);
	sq_getfloat(v, 4, &x1);
	sq_getfloat(v, 5, &y1);
	sq_getfloat(v, 6, &x2);
	sq_getfloat(v, 7, &y2);
	sq_getfloat(v, 8, &x3);
	sq_getfloat(v, 9, &y3);

	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);
	xyPnt d(x3, y3);

	sq_pushbool(v, xyLineLine(&a, &b, &c, &d));

	return 1;
}

SQInteger sqLineCircle(HSQUIRRELVM v) {
	SQFloat x0, y0, x1, y1, x2, y2, r;

	sq_getfloat(v, 2, &x0);
	sq_getfloat(v, 3, &y0);
	sq_getfloat(v, 4, &x1);
	sq_getfloat(v, 5, &y1);
	sq_getfloat(v, 6, &x2);
	sq_getfloat(v, 7, &y2);
	sq_getfloat(v, 8, &r);

	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);

	sq_pushbool(v, xyLineCircle(&a, &b, &c, r));

	return 1;
}

SQInteger sqLinePoint(HSQUIRRELVM v) {
	SQFloat x0, y0, x1, y1, x2, y2;

	sq_getfloat(v, 2, &x0);
	sq_getfloat(v, 3, &y0);
	sq_getfloat(v, 4, &x1);
	sq_getfloat(v, 5, &y1);
	sq_getfloat(v, 6, &x2);
	sq_getfloat(v, 7, &y2);

	sq_pushbool(v, xyLinePoint(x0, y0, x1, y1, x2, y2));

	return 1;
}


