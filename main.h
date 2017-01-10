/*===========*\
| MAIN HEADER |
\*===========*/

#ifndef _MAIN_H_
#define _MAIN_H_

//Operating System Flags
//#define _OS_WINDOWS_
//#define _OS_MAC_
//#define _OS_LINUX_
#define _OS_PANDORA_
//#define _OS_GCWZ_
//#define _OS_ANDROID_
//#define _OS_IOS_
//#define _OS_DINGOO_
//#define _OS_

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
#include "SDL.h"
#include "SDL_image.h"
#include "squirrel.h"
#include "sqstdio.h"
#include "sqstdaux.h"
#include "sqstdmath.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Squirrel/squirrel.h"
#include "Squirrel/sqstdio.h"
#include "Squirrel/sqstdaux.h"
#include "Squirrel/sqstdmath.h"
#endif

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


#endif
