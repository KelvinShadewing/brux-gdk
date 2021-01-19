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

setResolution(320, 180);

donut("src/assets.nut");
donut("src/actors.nut");
donut("src/shapes.nut");
donut("src/tilemap.nut");

::quit <- 0;
setFPS(30);

local map = Tilemap("res/test.json");

//Add search directories
tileSearchDir.push("res");

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

	if(keyPress(k_escape)) quit = true;
	update();
};