/*========*\
| TEST NUT |
\*========*/

//////////////////////
// GLOBAL VARIABLES //
//////////////////////


//Images
local sprCursor = newSprite("res/cursor.png", 16, 16, 0, 0, 1, 1, 1);
local imgBG = newSprite("res/background.png", 640, 360, 0, 0, 0, 0, 1);
local sprPlayer = newSprite("res/shooter/usp.png", 32, 32, 0, 0, 16, 16, 3);

//Misc
local quit = false;
local font = openFont("res/bobsgame.ttf", 12);
local actors = [];



///////////////////
// MAIN FUNCTION //
///////////////////

setScalingFilter(1);
setBackgroundColor(0);

while(!quit){
	if(keyPress(k_escape)) quit = true;
	drawSprite(imgBG, 0, 0, 0);
	drawSprite(sprCursor, 0, mouseX(), mouseY());
	update();
};

closeFont(font);