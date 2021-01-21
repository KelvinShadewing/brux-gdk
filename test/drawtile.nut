/*===============*\
| TILEMAP DRAWING |
\*===============*/

/*\
 # This app loads a tilemap and
 # renders it on screen.
 #
 # This comment is needlessly
 # decorated, but I don't care.
\*/

donut("src/assets.nut");
donut("src/actors.nut");
donut("src/shapes.nut");
donut("src/tilemap.nut");
print("");

::quit <- 0;
setFPS(30);

//Add search directories
tileSearchDir.push("res");
local map = Tilemap("res/test.json");
print(map.data.layers[0].type);

while(!quit)
{
	if(keyPress(k_space)) playSound(snBling, 0);
	if(keyPress(k_p))
	{
		if(!checkMusic()) playMusic(msBossa, -1);
		else if(musicPaused()) resumeMusic();
		else pauseMusic();
	}
	if(keyPress(k_s)) stopMusic();

	map.drawTiles(0, 0, 0, 0, 10, 10, "bg");
	drawSprite(map.tileset[0], 0, 0, 0);

	if(keyPress(k_escape)) quit = true;
	update();
};