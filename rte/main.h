/*===========*\
| MAIN HEADER |
\*===========*/

#ifndef _MAIN_H_
#define _MAIN_H_

//Headers
#include <stdio.h>
#include <sstream>
#include <string>
#include <stdarg.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <iostream>
#include <limits>
#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif // _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Squirrel/squirrel.h"
#include "Squirrel/sqstdio.h"
#include "Squirrel/sqstdaux.h"
#include "Squirrel/sqstdmath.h"

using namespace std;

//Defines
#ifdef SQUNICODE
	#define scvprintf vwprintf
	#else
	#define scvprintf vprintf
#endif

//Prototypes
int xyInit();
void xyStart();
void xyRun();
void xyEnd();
void xyPrint(HSQUIRRELVM v, const SQChar *s, ...);
void xyBindFunc(HSQUIRRELVM v, SQFUNCTION func, const SQChar *key);
void xyBindFunc(HSQUIRRELVM v, SQFUNCTION func, const SQChar *key, SQInteger nParams, const SQChar* sParams);
void xyBindAllFunctions(HSQUIRRELVM v);
int xyGetOS();
void xyError(HSQUIRRELVM v, const SQChar *s, ...);
void xyUpdate();


#endif
