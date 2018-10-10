/*========*\
| TEST NUT |
\*========*/
print("Test Nut");

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

//Misc
local quit = false;
::sprFont <- newSprite("cp437.png", 9, 16, 0, 0, 0, 0, 0);
print("Loaded font sprite.");
::fntTerm <- newFont(sprFont, 0, 0, 1);
print("Created font.");
local x = 0;



///////////////////
// MAIN FUNCTION //
///////////////////

setScalingFilter(1);
setResolution(400, 240);
setBackgroundColor(0);
setFPS(30);

while(!quit){
	if(keyPress(k_escape)) quit = true;
	x++;
	for(local i = 0; i < 48; i++){
		drawSprite(sprFont, x + i, 9 * i, 0);
	};
	drawText(fntTerm, 0, 16, "This is a test.");
	update();
};
