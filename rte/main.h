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

#ifdef _MSC_VER
#ifndef PATH_MAX
#define PATH_MAX _MAX_PATH
#endif
#define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
#endif
/*
	This requires MSVC? There needs to be a cross-platform alternative, otherwise it can't build.
*/

#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif // _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>
#include <sqstdmath.h>

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
