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
			local str = fileRead(filename);
			data = jsonRead(str);

			mapw = data.width;
			maph = data.height;
			tilew = data.tilewidth;
			tileh = data.tileheight;

			for(local i = 0; i < data.tilesets.len(); i++){
				tilebeg.push(data.tilesets[i].firstgid);
				tileend.push(data.tilesets[i].firstgid + data.tilesets[i]tilecount);

				//Extract filename
				local filename = data.tilesets[i].image;
				local shortname = findFileName(filename);

				local tempspr = findSprite("shortname");
				if(tempspr != -1) tileset.push(tempspr);
				else { //Search for file
					if(fileExists(filename)) tileset.push(newSprite(tileSearchDir[j] + "/" + shortname, data.tilewidth, data.tileheight, data.tilesests[i].margin, data.tilesets[i].spacing, 0, 0, 0);
					else for(local j = 0; j < tileSearchDir.len(); j++){
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
