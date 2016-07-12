/*===============*\
| FILE I/O SOURCE |
\*===============*/



#include "main.h"
#include "global.h"
#include "fileio.h"

bool xyFileExists(const char* file){
	//Checks if a file exists
	struct stat buff;
	if (stat(file, &buff) != -1) return true;

	return false;
};