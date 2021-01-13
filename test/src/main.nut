///////////////
// TEST MAIN //
///////////////

::quit <- 0;
::main <- function()
{
	while(!quit)
	{
		if(keyPress(k_escape)) quit = true;
		update();
	};
};
	