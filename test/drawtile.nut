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

//donut("src/assets.nut");
donut("src/shapes.nut");
donut("src/tilemap.nut");

setResolution(320, 180);
setDrawColor(0xffff);

::quit <- 0;
::camx <- 0;
::camy <- 0;
::layer1 <- true;
::layer2 <- true;

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

	if(keyDown(k_left)) camx -= 2;
	if(keyDown(k_right)) camx += 2;
	if(keyDown(k_up)) camy -= 2;
	if(keyDown(k_down)) camy += 2;

	if(keyPress(k_1)) layer1 = !layer1;
	if(layer1) map.drawTiles(-camx, -camy, floor(camx / 16), floor(camy / 16), 21, 13, "bg");
	if(keyPress(k_2)) layer2 = !layer2;
	if(layer2) map.drawTiles(-camx, -camy, floor(camx / 16), floor(camy / 16), 21, 13, "fg");

	map.drawShapes(-camx, -camy, "solid");

	if(keyPress(k_escape)) quit = true;
	update();
};