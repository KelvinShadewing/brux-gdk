////////////////
// TILED MAPS //
////////////////

::tileSearchDir <- ["."];

::findFileName <- function(path){
	if(typeof path != "string") return "";
	if(path.len() == 0) return "";

	for(local i = path.len() - 1; i >= 0; i--){
		if(path[i] == "/" || path[i] == "\\") return path.slice(i + 1);
	};

	return path;
};

::Tilemap <- class {
	data = {};
	tileset = [];
	tilebeg = [];
	tileend = [];
	tilew = 0;
	tileh = 0;
	mapw = 0;
	maph = 0;

	constructor(filename){
		if(fileExists(filename)){
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
					print("Added tempspr.");
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
					};
				};
			};
		};
	};

	function drawTile(tx, ty, dx, dy){
	};

	function draw(x, y){
	};
};
