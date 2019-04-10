/*==============*\
| TILEMAP HEADER |
\*==============*/

#ifndef _TILE_H_
#define _TILE_H_

#include "main.h"
#include "tinyxml2.h"
using namespace tinyxml2;

class xyTileMap {
	vector<Uint32> tith; //Tile threshold
	XMLDocument tmx; //Map file

	xyTileMap(const char* filename);
};

#endif
