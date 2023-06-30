//  Brux - Main
//  Copyright (C) 2016 KelvinShadewing
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

/*===========*\
| MAIN HEADER |
\*===========*/

#ifndef _MAIN_H_
#define _MAIN_H_

// Toggle features based on conditions
#ifndef _MSC_VER
	// If the compiler isn't MSVC, use std::chrono::steady_clock
	#define USE_CHRONO_STEADY_CLOCK
#endif

// Config header, used for optional libraries

#include "config.hpp"

// Headers

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include <stdarg.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <limits>
#include <sys/stat.h>
#include <bitset>
#ifdef USE_CHRONO_STEADY_CLOCK
#include <chrono>
#include <thread>
#endif

// If running on Windows, use Windows working directory functions.

#ifdef _WIN32
	#include "external/wdirent.h"
	#include <direct.h>
	#define getCD _getcwd
	#define getcwd _getcwd
	#define chdir _chdir
#else
	#include <dirent.h>
	#include <unistd.h>
	#define getCD getcwd
#endif // _WIN32

void __stack_chk_fail(void);

#include "external/cJSON.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdsystem.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

using namespace std;

// Defines

#ifdef SQUNICODE
	#define scvprintf vwprintf
	#else
	#define scvprintf vprintf
#endif

// Prototypes

int xyInit();
void xyStart();
void xyEnd();
void xyPrint(HSQUIRRELVM v, const SQChar *s, ...);
int xyGetOS();
void xyUpdate();

#endif
