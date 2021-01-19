////////////////
// TILED MAPS //
////////////////

::tileSearchDir <- ["."];

::findFileName <- function(path)
{
	if(typeof path != "string") return "";
	if(path.len() == 0) return "";

	for(local i = path.len() - 1; i >= 0; i--)
	{
		if(path[i] == "/" || path[i] == "\\") return path.slice(i + 1);
	}

	return path;
}

::Tilemap <- class
{
	data = {};
	tileset = [];
	tilebeg = [];
	tileend = [];
	tilew = 0;
	tileh = 0;
	mapw = 0;
	maph = 0;

	constructor(filename)
	{
		if(fileExists(filename))
		{
			data = jsonRead(fileRead(filename));

			mapw = data.width;
			maph = data.height;
			tilew = data.tilewidth;
			tileh = data.tileheight;

			for(local i = 0; i < data.tilesets.len(); i++)
			{
				print("Adding tile IDs...");
				tilebeg.push(data.tilesets[i].firstgid);
				tileend.push(data.tilesets[i].firstgid + data.tilesets[i].tilecount);
				print("Added tile IDs.");

				//Extract filename
				print("Get filename");
				local filename = data.tilesets[i].image;
				local shortname = findFileName(filename);
				print("Full map name: " + filename + ".");
				print("Short map name: " + shortname + ".");

				local tempspr = findSprite(shortname);
				print("Temp sprite: " + shortname);

				if(tempspr != -1)
				{
					tileset.push(tempspr);
					print("Added tempspr: " + shortname);
				}
				else
				{ //Search for file
					if(fileExists(filename))
					{
						print("Attempting to add full filename");
						tileset.push(newSprite(filename, data.tilewidth, data.tileheight, data.tilesests[i].margin, data.tilesets[i].spacing, 0, 0, 0));
						print("Added tileset " + shortname + ".");
					}
					else for(local j = 0; j < tileSearchDir.len(); j++)
					{
						if(fileExists(tileSearchDir[j] + "/" + shortname))
						{
							print("Adding from search path: " + tileSearchDir[j]);
							break;
						}
					}
				}
			}
		}
		else print("Map file " + filename + " does not exist!");
	}

	function drawTiles(x, y, mx, my, mw, mh, l)
	{ //@mx through @mh are the rectangle of tiles that will be drawn
		//Find layer
		local t = -1; //Target layer
		foreach(i in data.layers)
		{
			if(data.layers[i]["type"] == "tilemap" && data.layers[i].name == l)
			{
				t = i;
				break;
			}
		}
		if(t == -1) return;

		//Make sure values are in range
		if(data.layers[t].width < mx + mw) mw = data.layers[t].width - mx;
		if(data.layers[t].height < my + mh) mh = data.layers[t].height - my;

		for(local i = mx; i < mx + mw; i++)
		{
			for(local j = my; j < my + mh; j++)
			{
				local n = data.layers[t].data[(j * data.layers[t].width) + i]; //Number value of the tile
				if(n != 0)
				{

				}
			}
		}
	}
};
