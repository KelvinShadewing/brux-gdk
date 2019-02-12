/*==============*\
| TILEMAP HEADER |
\*==============*/

#ifndef _TILE_H_
#define _TILE_H_

#include "tinyxml2.h"
using namespace tinyxml2;

class xyTileMap {
	vector<Uint32> tith(0); //Tile threshold
	XMLDocument tmx; //Map file

	xyTileMap(char** filename);
};

#endif
