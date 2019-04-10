/*==============*\
| TILEMAP SOURCE |
\*==============*/

#include "main.h"
#include "graphics.h"
#include "sprite.h"
#include "tile.h"
#include "fileio.h"
using namespace tinyxml2;

xyTileMap::xyTileMap(const char* filename){
	//Attempt to load map file
	if(xyFileExists(filename)){
		XMLError eResult = tmx.LoadFile(filename);
	};
};
