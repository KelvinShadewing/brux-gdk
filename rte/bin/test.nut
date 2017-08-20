/*========*\
| TEST NUT |
\*========*/
print("Test Nut");

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

//Misc
local quit = false;



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
	update();
};