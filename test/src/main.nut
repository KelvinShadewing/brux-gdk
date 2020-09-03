///////////////
// TEST MAIN //
///////////////

::quit <- 0;
::main <- function(){
	setFPS(30);

	local map = Tilemap("res/test.json");

	//Add search directories
	tileSearchDir.push("res");

	while(!quit){
		if(keyPress(k_escape)) quit = true;
		update();
	};
};
