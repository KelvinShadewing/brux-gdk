/*========*\
| TEST NUT |
\*========*/
print("Test Nut");

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

//Misc
local quit = false;
local font = openFont("res/bobsgame.ttf", 8);



///////////////////
// MAIN FUNCTION //
///////////////////

setScalingFilter(1);
setResolution(320, 240);
setBackgroundColor(0);
setFPS(60);

local scale = 1;
local angle = 0;

local shipx = -32;

while(!quit){
	if(keyPress(k_escape)) quit = true;
	drawText(16, 16, "This is a test nut. No game has been loaded.", font, 0xF8F8F8, 0, 0);
	update();
};

closeFont(font);