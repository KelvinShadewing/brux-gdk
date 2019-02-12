/*==============*\
| TILEMAP SOURCE |
\*==============*/

#include "main.h"
#include "graphics.h"
#include "sprite.h"
#include "tile.h"
using namespace tinyxml2;

xyTileMap::xyTileMap(char** filename){
	//Attempt to load map file
	if(xyFileExists(filename)){
		XMLError eResult = tmx.LoadFile(filename);
	};
};
