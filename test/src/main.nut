///////////////
// TEST MAIN //
///////////////

::quit <- 0;
::main <- function()
{
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
};
	